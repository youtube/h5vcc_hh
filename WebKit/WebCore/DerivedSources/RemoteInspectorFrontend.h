// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef RemoteInspectorFrontend_h
#define RemoteInspectorFrontend_h

#include <wtf/PassRefPtr.h>

namespace WebCore {

class InspectorArray;
class InspectorClient;
class InspectorObject;
class InspectorValue;
class String;

class RemoteInspectorFrontend {
public:
    RemoteInspectorFrontend(InspectorClient* inspectorClient) : m_inspectorClient(inspectorClient) { }

    void didToggleStyleEnabled(long callId, PassRefPtr<InspectorValue> style);
    void didChangeTagName(long callId, long nodeId);
    void didSaveSessionSettings(long callId);
    void didRemoveNode(long callId, long nodeId);
    void didAddScriptToEvaluateOnLoad(long callId);
    void didDisableMonitoringXHR(long callId);
    void didGetComputedStyle(long callId, PassRefPtr<InspectorValue> style);
    void didApplyDomChange(long callId, bool success);
    void didGetRuleRangesForStyleSheetId(long callId);
    void didReloadPage(long callId);
    void didDidEvaluateForTestInFrontend(long callId);
    void didSetOuterHTML(long callId, long nodeId);
    void didSetDOMStorageItem(long callId);
    void didGetStyles(long callId, PassRefPtr<InspectorValue> styles);
    void didClearConsoleMessages(long callId);
    void didDisableSearchingForNode(long callId);
    void didStoreLastActivePanel(long callId);
    void didGetCookies(long callId);
    void addRecordToTimeline(PassRefPtr<InspectorObject> record);
    void childNodeRemoved(long parentId, long id);
    void didStartTimelineProfiler(long callId);
    void didGetEventListenersForNode(long callId, long nodeId, PassRefPtr<InspectorArray> listenersArray);
    void didDisableResourceTracking(long callId);
    void setDetachedRoot(PassRefPtr<InspectorObject> root);
    void didReleaseWrapperObjectGroup(long callId);
    void didHighlightDOMNode(long callId);
    void didAddRule(long callId, PassRefPtr<InspectorValue> rule, bool selectorAffectsNode);
    void didGetInlineStyle(long callId, PassRefPtr<InspectorValue> style);
    void didSetInjectedScriptSource(long callId);
    void didRemoveDOMStorageItem(long callId);
    void didGetStyleSheet(long callId, PassRefPtr<InspectorValue> styleSheet);
    void didDispatchOnInjectedScript(long callId);
    void didEnableMonitoringXHR(long callId);
    void didAddInspectedNode(long callId);
    void attributesUpdated(long id, PassRefPtr<InspectorArray> attributes);
    void didSetTextNodeValue(long callId);
    void didSaveApplicationSettings(long callId);
    void didGetAllStyles(long callId, PassRefPtr<InspectorArray> styles);
    void didPerformSearch(long callId);
    void didPushNodeByPathToFrontend(long callId, long nodeId);
    void setChildNodes(long parentId, PassRefPtr<InspectorArray> nodes);
    void didGetApplicationCaches(long callId);
    void didStopTimelineProfiler(long callId);
    void didGetResourceContent(long callId);
    void addNodesToSearchResult(PassRefPtr<InspectorArray> nodeIds);
    void setDocument(PassRefPtr<InspectorValue> root);
    void didSetStyleText(long callId, bool success);
    void didHideDOMNodeHighlight(long callId);
    void didCopyNode(long callId);
    void didSetRuleSelector(long callId, PassRefPtr<InspectorValue> rule, bool selectorAffectsNode);
    void didRemoveAllScriptsToEvaluateOnLoad(long callId);
    void didGetDatabaseTableNames(long callId);
    void didSetStyleProperty(long callId, bool success);
    void didApplyStyleText(long callId, bool success, PassRefPtr<InspectorValue> style, PassRefPtr<InspectorArray> changedProperties);
    void didEnableResourceTracking(long callId);
    void childNodeCountUpdated(long id, int newValue);
    void didSearchCanceled(long callId);
    void childNodeInserted(long parentId, long prevId, PassRefPtr<InspectorObject> node);
    void didGetChildNodes(long callId);
    void didGetDOMStorageEntries(long callId);
    void didDeleteCookie(long callId);
    void didGetOuterHTML(long callId, const String& outerHTML);
    void didEnableSearchingForNode(long callId);

private:
    InspectorClient* m_inspectorClient;
};

} // namespace WebCore
#endif // !defined(RemoteInspectorFrontend_h)

