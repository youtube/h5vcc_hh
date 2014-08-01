/*
 Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)
 Copyright (C) 2014 FactorY Media Production GmbH
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License as published by the Free Software Foundation; either
 version 2 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.

 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
 */

/* FYWEBKITMOD BEGIN integrated from https://gitorious.org/webkit/noamrs-webkit/source/cb48ff9f4067b8ebcbb8a54e9dfef2d6fda0b82f:WebCore/platform/graphics/opengl/TextureMapperGL.cpp */

#include "config.h"
#include "TextureMapperGL.h"

#include "GraphicsContext.h"
#include "HashMap.h"
#include "Image.h"
#include "PassRefPtr.h"
#include "RefCounted.h"
#include "Timer.h"

#include <stdio.h>
#if PLATFORM(QT)
#ifdef Q_WS_MAC
#include <gl.h>
#elif defined(QT_OPENGL_ES_2)
#define TEXMAP_OPENGL_ES2
#include <GLES2/gl2.h>
#else
#include <GL/gl.h>
#endif
#endif
#ifndef TEXMAP_OPENGL_ES2

extern "C" {
    void glUniform1f(GLint, GLfloat);
    void glUniform1i(GLint, GLint);
    void glVertexAttribPointer(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *);
    void glUniform4f(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
    void glShaderSource(GLuint, GLsizei, const char **, const GLint *);
    GLuint glCreateShader(GLenum);
    void glShaderSource(GLuint, GLsizei, const char **, const GLint *);
    void glCompileShader(GLuint);
    void glDeleteShader(GLuint);
    void glUniformMatrix4fv(GLint, GLsizei, GLboolean, const GLfloat *);
    GLuint glCreateProgram();
    void glAttachShader(GLuint, GLuint);
    void glLinkProgram(GLuint);
    void glUseProgram(GLuint);
    void glDisableVertexAttribArray(GLuint);
    void glEnableVertexAttribArray(GLuint);
    void glBindFramebuffer(GLenum target, GLuint framebuffer);
    void glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
    void glGenFramebuffers(GLsizei n, GLuint *framebuffers);
    void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params);
    void glBindBuffer(GLenum, GLuint);
    void glDeleteBuffers(GLsizei, const GLuint*);
    void glGenBuffers(GLsizei, GLuint*);
    void glBufferData(GLenum, GLsizeiptr, const GLvoid*, GLenum);
    void glBufferSubData(GLenum, GLsizeiptr, GLsizeiptr, const GLvoid*);
    void glGetProgramInfoLog(GLuint program, GLsizei, GLsizei*, GLchar*);

#ifndef Q_WS_MAC
    GLint glGetUniformLocation(GLuint, const GLchar *);
    GLint glGetAttribLocation(GLuint, const GLchar *);
#endif
}
#endif


namespace WTF {

// StringHash is the default hash for String
template<typename T> struct DefaultHash;
template<> struct HashTraits<WebCore::FloatRect> : WTF::GenericHashTraits<WebCore::FloatRect> {
    static void constructDeletedValue(WebCore::FloatRect& slot) { slot = WebCore::FloatRect(); }
    static bool isDeletedValue(const WebCore::FloatRect& value) { return value == WebCore::FloatRect(); }
};

template<> struct DefaultHash<WebCore::FloatRect> {
    struct Hash {
        static int hash(const WebCore::FloatRect& rect)
        {
            return int(rect.x() * 0x10) | (int(rect.y() * 0x10) << 4) | (int(rect.height() * 0x100) << 8) | (int(rect.width() * 0x100) << 20);
        }

        static bool equal(const WebCore::FloatRect& a, const WebCore::FloatRect& b) { return a == b; }

        static const bool safeToCompareToEmptyOrDeleted = true;
    };
};

}


namespace WebCore {

inline static void debugGLCommand(const char* command, int line)
{
    const GLenum err = glGetError();
    if (err)
        qFatal("[TextureMapper GL] Command failed: Line %d\n\toperation: %s, \n\terror: %x\n", line, command, err);
}

#define DEBUG_GL_COMMANDS

#ifdef DEBUG_GL_COMMANDS
#define GL_CMD(x) {x, debugGLCommand(#x, __LINE__); }
#else
#define GL_CMD(x) x
#endif

struct TexmapGLVboRepository {
    typedef HashMap<FloatRect, GLuint> VboMap;
    VboMap vboMap;
};

static TexmapGLVboRepository gVboRepository;

static void loadRectToShader(GLuint id, const FloatRect& rect)
{
    GLuint vbo;
    TexmapGLVboRepository::VboMap::iterator it = gVboRepository.vboMap.find(rect);
    if (it == gVboRepository.vboMap.end()) {
        const FloatQuad quad(rect);
        GL_CMD(glGenBuffers(1, &vbo))
        GL_CMD(glBindBuffer(GL_ARRAY_BUFFER, vbo))
        GL_CMD(glBufferData(GL_ARRAY_BUFFER, sizeof(FloatQuad), &quad, GL_STATIC_DRAW))
        gVboRepository.vboMap.add(rect, vbo);
    } else {
        vbo = it->second;
        GL_CMD(glBindBuffer(GL_ARRAY_BUFFER, vbo))
    }
    GL_CMD(glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, 0, 0))
}

class BitmapTextureGL : public BitmapTexture {
    friend class TextureMapperGL;
public:
    virtual void destroy();
    virtual IntSize size() const;
    virtual bool isValid() const;
    virtual void reset(const IntSize&, bool opaque);
    virtual PlatformGraphicsContext* beginPaint(const IntRect& dirtyRect);
    virtual void endPaint();
    virtual void setContentsToImage(Image*);
private:
    GLuint m_id;
    NativeImagePtr m_image;
    FloatSize m_relativeSize;
    bool m_opaque;
    IntSize m_textureSize;
    RefPtr<RGBA32PremultimpliedBuffer> m_buffer;
    IntRect m_dirtyRect;
    FloatRect m_sourceRect;
    GLuint m_fbo;
    IntSize m_actualSize;
    bool m_surfaceNeedsReset;
    BitmapTextureGL()
        : m_id(0)
        , m_image(0)
        , m_opaque(false)
        , m_fbo(0)
        , m_surfaceNeedsReset(true)
    {
    }
};

static struct TexmapShaderInfo {
    enum ShaderProgramIndex {
        SimpleProgram,
        OpacityProgram,
        OpacityAndMaskProgram,
        TargetProgram,
        NumPrograms
    };

    enum ShaderVariableIndex {
        InMatrixVariable,
        InTexCoordSourceVariable,
        InVertexVariable,
        InTexCoordMaskVariable,

        OpacityVariable,
        SourceTextureVariable,
        MaskTextureVariable,
        NumVariables
    };

    struct ProgramInfo {
        GLuint id;
        GLint vars[NumVariables];
    };

    GLint getUniformLocation(ShaderProgramIndex prog, ShaderVariableIndex var, const char* name)
    {
        return programs[prog].vars[var] = glGetUniformLocation(programs[prog].id, name);
    }

    GLint getAttribLocation(ShaderProgramIndex prog, ShaderVariableIndex var, const char* name)
    {
        return programs[prog].vars[var] = glGetAttribLocation(programs[prog].id, name);
    }

    void createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource, ShaderProgramIndex index)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        GL_CMD(glShaderSource(vertexShader, 1, &vertexShaderSource, 0))
        GL_CMD(glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0))
        GLuint programID = glCreateProgram();
        GL_CMD(glCompileShader(vertexShader))
        GL_CMD(glCompileShader(fragmentShader))
        GL_CMD(glAttachShader(programID, vertexShader))
        GL_CMD(glAttachShader(programID, fragmentShader))
        GL_CMD(glLinkProgram(programID))
        programs[index].id = programID;
        char infoLog[1024];
        int len;
        glGetProgramInfoLog(programID, 1024, &len, infoLog);
        printf("%s\n", infoLog);
    }

    ProgramInfo programs[NumPrograms];

} gShaderInfo;

#define TEXMAP_GET_SHADER_VAR_LOCATION(type, prog, var) if (gShaderInfo.get##type##Location(TexmapShaderInfo::prog##Program, TexmapShaderInfo::var##Variable, #var) < 0) qWarning("Couldn't find variable "#var" in program "#prog);
#define TEXMAP_BUILD_SHADER(program) gShaderInfo.createShaderProgram(vertexShaderSource##program, fragmentShaderSource##program, TexmapShaderInfo::program##Program);

TextureMapperGL::TextureMapperGL(GraphicsContext* gc)
    : TextureMapper(gc)
    , m_curProgram(TexmapShaderInfo::TargetProgram)
{
    static bool shadersCompiled = false;
    if (shadersCompiled)
        return;
    shadersCompiled = true;
#ifndef TEXMAP_OPENGL_ES2
#define OES2_PERCISION_DEFINITIONS \
    "#define lowp\n#define highp\n"
#else
#define OES2_PERCISION_DEFINITIONS
#endif

    const char* fragmentShaderSourceOpacityAndMask =
            OES2_PERCISION_DEFINITIONS
"               uniform sampler2D SourceTexture, MaskTexture;                       \n"
"               uniform lowp float Opacity;                                         \n"
"               varying highp vec2 OutTexCoordSource, OutTexCoordMask;              \n"
"               void main(void)                                                     \n"
"               {                                                                   \n"
"                   lowp vec4 color = texture2D(SourceTexture, OutTexCoordSource);  \n"
"                   lowp vec4 maskColor = texture2D(MaskTexture, OutTexCoordMask);  \n"
"                   lowp float o = Opacity * maskColor.a;                           \n"
"                   gl_FragColor = vec4(color.rgb * o, color.a * o);                \n"
"               }                                                               \n";

    const char* vertexShaderSourceOpacityAndMask =
            OES2_PERCISION_DEFINITIONS
"               uniform mat4 InMatrix;                                      \n"
"               attribute vec4 InTexCoordSource, InTexCoordMask, InVertex;      \n"
"               varying highp vec2 OutTexCoordSource, OutTexCoordMask;      \n"
"               void main(void)                                             \n"
"               {                                                           \n"
"                   OutTexCoordSource = vec2(InTexCoordSource);               \n"
"                   OutTexCoordMask = vec2(InTexCoordMask);                   \n"
"                   gl_Position = InMatrix * InVertex;                      \n"
"               }                                                           \n";

    const char* fragmentShaderSourceOpacity =
            OES2_PERCISION_DEFINITIONS
"               uniform sampler2D SourceTexture;                                    \n"
"               uniform lowp float Opacity;                                         \n"
"               varying highp vec2 OutTexCoordSource;                               \n"
"               void main(void)                                                     \n"
"               {                                                                   \n"
"                   lowp vec4 color = texture2D(SourceTexture, OutTexCoordSource);  \n"
"                   gl_FragColor = vec4(color.rgb * Opacity, color.a * Opacity);    \n"
"               }                                                                   \n";

    const char* vertexShaderSourceOpacity =
            OES2_PERCISION_DEFINITIONS
"               uniform mat4 InMatrix;                              \n"
"               attribute vec4 InTexCoordSource, InVertex;            \n"
"               varying highp vec2 OutTexCoordSource;               \n"
"               void main(void)                                     \n"
"               {                                                   \n"
"                   OutTexCoordSource = vec2(InTexCoordSource);       \n"
"                   gl_Position = InMatrix * InVertex;              \n"
"               }                                                   \n";

    const char* fragmentShaderSourceSimple =
            OES2_PERCISION_DEFINITIONS
"               uniform sampler2D SourceTexture;                                        \n"
"               varying highp vec2 OutTexCoordSource;                                   \n"
"               void main(void)                                                         \n"
"               {                                                                       \n"
"                   lowp vec4 color = texture2D(SourceTexture, OutTexCoordSource);      \n"
"                   gl_FragColor = color;                                               \n"
"               }                                                                       \n";

    const char* vertexShaderSourceSimple = vertexShaderSourceOpacity;

    const char* fragmentShaderSourceTarget =
            OES2_PERCISION_DEFINITIONS
"               uniform sampler2D SourceTexture;                                            \n"
"               uniform lowp float Opacity;                                                 \n"
"               varying highp vec2 OutTexCoordSource;                                       \n"
"               void main(void)                                                             \n"
"               {                                                                           \n"
"                   lowp vec4 color = texture2D(SourceTexture, OutTexCoordSource);          \n"
"                   gl_FragColor = vec4(color.bgr * Opacity, color.a * Opacity);            \n"
"               }                                                                           \n";

    const char* vertexShaderSourceTarget =
            OES2_PERCISION_DEFINITIONS
"               attribute vec4 InTexCoordSource, InVertex;            \n"
"               varying highp vec2 OutTexCoordSource;               \n"
"               void main(void)                                     \n"
"               {                                                   \n"
"                   OutTexCoordSource = vec2(InTexCoordSource);     \n"
"                   gl_Position = InVertex;                         \n"
"               }                                                   \n";

    TEXMAP_BUILD_SHADER(Simple)
    TEXMAP_BUILD_SHADER(Opacity)
    TEXMAP_BUILD_SHADER(OpacityAndMask)
    TEXMAP_BUILD_SHADER(Target)

    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, OpacityAndMask, InVertex)
    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, OpacityAndMask, InTexCoordSource)
    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, OpacityAndMask, InTexCoordMask)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, OpacityAndMask, InMatrix)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, OpacityAndMask, SourceTexture)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, OpacityAndMask, MaskTexture)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, OpacityAndMask, Opacity)

    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, Opacity, InVertex)
    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, Opacity, InTexCoordSource)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, Opacity, InMatrix)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, Opacity, SourceTexture)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, Opacity, Opacity)

    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, Simple, InVertex)
    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, Simple, InTexCoordSource)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, Simple, InMatrix)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, Simple, SourceTexture)

    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, Target, InTexCoordSource)
    TEXMAP_GET_SHADER_VAR_LOCATION(Attrib, Target, InVertex)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, Target, SourceTexture)
    TEXMAP_GET_SHADER_VAR_LOCATION(Uniform, Target, Opacity)
}

void TextureMapperGL::drawTexture(const BitmapTexture& texture, const IntRect& targetRect, const TransformationMatrix& mvMatrix, float opacity, const BitmapTexture* maskTexture)
{
    const BitmapTextureGL& textureGL = static_cast<const BitmapTextureGL&>(texture);
    if (!texture.isValid())
        return;

    TexmapShaderInfo::ShaderProgramIndex program;
    if (maskTexture)
        program = TexmapShaderInfo::OpacityAndMaskProgram;
    else if (opacity < 0.99)
        program = TexmapShaderInfo::OpacityProgram;
    else
        program = TexmapShaderInfo::SimpleProgram;
    const TexmapShaderInfo::ProgramInfo& programInfo = gShaderInfo.programs[program];
    if (m_curProgram != program) {
        GL_CMD(glUseProgram(programInfo.id))
        GL_CMD(glDisableVertexAttribArray(gShaderInfo.programs[m_curProgram].vars[TexmapShaderInfo::InTexCoordSourceVariable]))
        GL_CMD(glDisableVertexAttribArray(gShaderInfo.programs[m_curProgram].vars[TexmapShaderInfo::InVertexVariable]))
        m_curProgram = program;
        GL_CMD(glEnableVertexAttribArray(programInfo.vars[TexmapShaderInfo::InTexCoordSourceVariable]))
        GL_CMD(glEnableVertexAttribArray(programInfo.vars[TexmapShaderInfo::InVertexVariable]))
    }

    GL_CMD(glDisable(GL_DEPTH_TEST))
    GL_CMD(glDisable(GL_STENCIL_TEST))

    GL_CMD(glActiveTexture(GL_TEXTURE0))
    GL_CMD(glBindTexture(GL_TEXTURE_2D, textureGL.m_id))
    loadRectToShader(programInfo.vars[TexmapShaderInfo::InVertexVariable], targetRect);
    loadRectToShader(programInfo.vars[TexmapShaderInfo::InTexCoordSourceVariable], textureGL.m_sourceRect);
    TransformationMatrix matrix = TransformationMatrix(m_projectionMatrix).multLeft(mvMatrix);
    const GLfloat m4[] = {
        matrix.m11(), matrix.m12(), matrix.m13(), matrix.m14(),
        matrix.m21(), matrix.m22(), matrix.m23(), matrix.m24(),
        matrix.m31(), matrix.m32(), matrix.m33(), matrix.m34(),
        matrix.m41(), matrix.m42(), matrix.m43(), matrix.m44()
    };
    glUniformMatrix4fv(programInfo.vars[TexmapShaderInfo::InMatrixVariable], 1, GL_FALSE, m4);
    GL_CMD(glUniform1i(programInfo.vars[TexmapShaderInfo::SourceTextureVariable], 0))

    if (maskTexture && maskTexture->isValid()) {
        const BitmapTextureGL* maskTextureGL = static_cast<const BitmapTextureGL*>(maskTexture);
        GL_CMD(glActiveTexture(GL_TEXTURE1))
        GL_CMD(glBindTexture(GL_TEXTURE_2D, maskTextureGL->m_id))
        loadRectToShader(programInfo.vars[TexmapShaderInfo::InTexCoordMaskVariable], maskTextureGL->m_sourceRect);
        GL_CMD(glEnableVertexAttribArray(programInfo.vars[TexmapShaderInfo::InTexCoordMaskVariable]))
        GL_CMD(glUniform1i(programInfo.vars[TexmapShaderInfo::MaskTextureVariable], 1))
        GL_CMD(glActiveTexture(GL_TEXTURE0))
    }

    if (program != TexmapShaderInfo::SimpleProgram)
        GL_CMD(glUniform1f(programInfo.vars[TexmapShaderInfo::OpacityVariable], opacity))

    if (textureGL.m_opaque && opacity > 0.99 && !maskTexture)
        GL_CMD(glDisable(GL_BLEND))
    else {
        GL_CMD(glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA))
        GL_CMD(glEnable(GL_BLEND))
    }

    GL_CMD(glDrawArrays(GL_TRIANGLE_FAN, 0, 4))
}


const char* TextureMapperGL::type() const
{
    return "OpenGL";
}

void BitmapTextureGL::reset(const IntSize& newSize, bool opaque)
{
    BitmapTexture::reset(newSize, opaque);
    m_image = 0;
    IntSize newTextureSize = npot(newSize);
    bool justCreated = false;
    if (!m_id) {
        GL_CMD(glGenTextures(1, &m_id))
        justCreated = true;
    }

    if (justCreated || newTextureSize.width() > m_textureSize.width() || newTextureSize.height() > m_textureSize.height()) {
        printf("[TextureMapperGL] Creating texture. ID: %d; Size: %d,%d\n", m_id, newTextureSize.width(), newTextureSize.height());
        m_textureSize = newTextureSize;
        GL_CMD(glBindTexture(GL_TEXTURE_2D, m_id))
        GL_CMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
        GL_CMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
        GL_CMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
        GL_CMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))
        GL_CMD(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureSize.width(), m_textureSize.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0))
    }
    m_actualSize = newSize;
    m_relativeSize = FloatSize(float(newSize.width()) / m_textureSize.width(), float(newSize.height()) / m_textureSize.height());
    m_sourceRect = FloatRect(0, 0, m_relativeSize.width(), m_relativeSize.height());
    m_opaque = opaque;
    m_surfaceNeedsReset = true;
}

PlatformGraphicsContext* BitmapTextureGL::beginPaint(const IntRect& dirtyRect)

{
    m_buffer = RGBA32PremultimpliedBuffer::create();
    m_dirtyRect = dirtyRect;
    return m_buffer->beginPaint(dirtyRect, m_opaque);
}

void BitmapTextureGL::endPaint()
{
    if (!m_buffer)
        return;
    m_buffer->endPaint();
    GL_CMD(glBindTexture(GL_TEXTURE_2D, m_id))
    GL_CMD(glTexSubImage2D(GL_TEXTURE_2D, 0, m_dirtyRect.x(), m_dirtyRect.y(), m_dirtyRect.width(), m_dirtyRect.height(), GL_RGBA, GL_UNSIGNED_BYTE, m_buffer->data()))
    m_buffer.clear();
}

struct TexmapGLShaderTextures {
    struct Entry {
        GLuint texture;
        int refCount;
    };
    HashMap<NativeImagePtr, Entry> imageToTexture;
    GLuint findOrCreate(NativeImagePtr image, bool& found)
    {
        HashMap<NativeImagePtr, Entry>::iterator it = imageToTexture.find(image);
        found = false;
        if (it != imageToTexture.end()) {
            it->second.refCount++;
            found = true;
            return it->second.texture;
        }
        Entry entry;
        GL_CMD(glGenTextures(1, &entry.texture));
        entry.refCount = 1;
        imageToTexture.add(image, entry);
        return entry.texture;
    }

    bool deref(NativeImagePtr image)
    {
        HashMap<NativeImagePtr, Entry>::iterator it = imageToTexture.find(image);
        if (it != imageToTexture.end()) {
            if (it->second.refCount < 2) {
                imageToTexture.remove(it);
                return false;
            }
        }
        return true;
    }
};

static TexmapGLShaderTextures gTextureRepository;

void BitmapTextureGL::setContentsToImage(Image* image)
{
    NativeImagePtr nativeImage = image ? image->nativeImageForCurrentFrame() : 0;
    if (!image || !nativeImage) {
        if (m_image)
            destroy();
        return;
    }

    if (nativeImage == m_image)
        return;
    bool found = false;
    GLuint newTextureID = gTextureRepository.findOrCreate(nativeImage, found);
    if (newTextureID != m_id) {
        destroy();
        m_id = newTextureID;
        reset(image->size(), false);
        m_image = nativeImage;
        printf("[TextureMapperGL] Creating texture from directly composited image. ID: %d; Size: %d,%d\n", m_id, image->width(), image->height());
        if (!found) {
            GraphicsContext gc(beginPaint(IntRect(0, 0, m_textureSize.width(), m_textureSize.height())));
            gc.drawImage(image, DeviceColorSpace, IntPoint(0, 0), CompositeCopy);
            endPaint();
        }
    }
}

void BitmapTextureGL::destroy()
{
    if (m_id && (!m_image || !gTextureRepository.deref(m_image))) {
        GL_CMD(glDeleteTextures(1, &m_id))
        printf("[TextureMapperOpenGL] Deleting texture %d, size: %d,%d\n", m_id, m_textureSize.width(), m_textureSize.height());
    }
    if (m_fbo)
        GL_CMD(glDeleteFramebuffers(1, &m_fbo))

    m_fbo = 0;
    m_id = 0;
    m_textureSize = IntSize();
    m_relativeSize = FloatSize(1, 1);
}
bool BitmapTextureGL::isValid() const
{
    return m_id;
}

IntSize BitmapTextureGL::size() const
{
    return m_textureSize;
}

static inline TransformationMatrix createProjectionMatrix(const IntSize& size, bool flip)
{
    return TransformationMatrix(2.0 / float(size.width()), 0, 0, 0,
                                0, (flip ? -2.0 : 2.0) / float(size.height()), 0, 0,
                                0, 0, -0.000001, 0,
                                -1, flip ? 1 : -1, 0, 1);
}

void TextureMapperGL::cleanup()
    {
    for (TexmapGLVboRepository::VboMap::iterator it = gVboRepository.vboMap.begin(); it != gVboRepository.vboMap.end(); ++it) {
        printf("[TextureMapperGL] Deleting vbo %d, %f %f %f %f\n", it->second, it->first.x(), it->first.y(), it->first.width(), it->first.height());
        GL_CMD(glDeleteBuffers(1, &it->second))
    }
    gVboRepository.vboMap.clear();
}


void TextureMapperGL::bindSurface(BitmapTexture *surfacePointer)
{
    BitmapTextureGL* surface = static_cast<BitmapTextureGL*>(surfacePointer);

    if (!surface)
        return;
    TransformationMatrix matrix = createProjectionMatrix(surface->size(), false);
    matrix.translate(-surface->offset().x(), -surface->offset().y());

    if (surface->m_surfaceNeedsReset || !surface->m_fbo) {
        if (!surface->m_fbo)
            GL_CMD(glGenFramebuffers(1, &surface->m_fbo))
        GL_CMD(glBindFramebuffer(GL_FRAMEBUFFER, surface->m_fbo))
        GL_CMD(glBindTexture(GL_TEXTURE_2D, 0))
        GL_CMD(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, surface->m_id, 0))
        GL_CMD(glClearColor(0, 0, 0, 0))
        GL_CMD(glClear(GL_COLOR_BUFFER_BIT))
        surface->m_surfaceNeedsReset = false;
    } else {
        GL_CMD(glBindFramebuffer(GL_FRAMEBUFFER, surface->m_fbo))
    }

    GL_CMD(glViewport(0, 0, surface->size().width(), surface->size().height()))
    m_projectionMatrix = matrix;
}

void TextureMapperGL::setClip(const IntRect& rect)
{
    GL_CMD(glScissor(rect.x(), rect.y(), rect.width(), rect.height()))
    GL_CMD(glEnable(GL_SCISSOR_TEST))
}


void TextureMapperGL::paintToTarget(const BitmapTexture& aSurface, const IntSize& surfaceSize, const TransformationMatrix& transform, float opacity, const IntRect& visibleRect)
{
    const BitmapTextureGL& surface = static_cast<const BitmapTextureGL&>(aSurface);
    // create the model-view-projection matrix to display on screen
    TransformationMatrix mvpMatrix = createProjectionMatrix(surfaceSize, true).multLeft(transform);
    const FloatQuad finalQuad = mvpMatrix.mapQuad(FloatQuad(FloatRect(surface.offset().x(), surface.offset().y(), surface.m_actualSize.width(), surface.m_actualSize.height())));

    // We already blended the alpha in; the result is premultiplied
    GL_CMD(glUseProgram(gShaderInfo.programs[TexmapShaderInfo::TargetProgram].id))
    GL_CMD(glBindFramebuffer(GL_FRAMEBUFFER, 0))
    GL_CMD(glViewport(0, 0, surfaceSize.width(), surfaceSize.height()))
    GL_CMD(glDisable(GL_STENCIL_TEST))
    const TexmapShaderInfo::ProgramInfo& programInfo = gShaderInfo.programs[TexmapShaderInfo::TargetProgram];
    GL_CMD(glUniform1f(programInfo.vars[TexmapShaderInfo::OpacityVariable], opacity))
    GL_CMD(glActiveTexture(GL_TEXTURE0))
    GL_CMD(glBindTexture(GL_TEXTURE_2D, surface.m_id))
    GL_CMD(glUniform1i(programInfo.vars[TexmapShaderInfo::SourceTextureVariable], 0))
    GL_CMD(glEnableVertexAttribArray(programInfo.vars[TexmapShaderInfo::InTexCoordSourceVariable]))
    GL_CMD(glEnableVertexAttribArray(programInfo.vars[TexmapShaderInfo::InVertexVariable]))
    GL_CMD(glBindBuffer(GL_ARRAY_BUFFER, 0))
    GL_CMD(glVertexAttribPointer(programInfo.vars[TexmapShaderInfo::InVertexVariable], 2, GL_FLOAT, GL_FALSE, 0, &finalQuad))
    loadRectToShader(programInfo.vars[TexmapShaderInfo::InTexCoordSourceVariable], surface.m_sourceRect);
    GL_CMD(glBindBuffer(GL_ARRAY_BUFFER, 0))
    GL_CMD(glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA))
    GL_CMD(glEnable(GL_BLEND))
    setClip(visibleRect);

    GL_CMD(glDrawArrays(GL_TRIANGLE_FAN, 0, 4))
    GL_CMD(glDisableVertexAttribArray(programInfo.vars[TexmapShaderInfo::InTexCoordSourceVariable]))
    GL_CMD(glDisableVertexAttribArray(programInfo.vars[TexmapShaderInfo::InVertexVariable]))
    GL_CMD(glUseProgram(0))
    m_curProgram = TexmapShaderInfo::TargetProgram;
}

PassRefPtr<BitmapTexture> TextureMapperGL::createTexture() { return adoptRef(new BitmapTextureGL()); }

};

/* FYWEBKITMOD END */
