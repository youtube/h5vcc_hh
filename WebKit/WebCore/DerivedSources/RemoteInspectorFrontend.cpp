// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "config.h"
#include "RemoteInspectorFrontend.h"

#if ENABLE(INSPECTOR)

#include "InspectorClient.h"
#include "InspectorValues.h"
#include "PlatformString.h"

namespace WebCore {

void RemoteInspectorFrontend::addRecordToTimeline(PassRefPtr<InspectorObject> record)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("addRecordToTimeline");
    arguments->push(record);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::addNodesToSearchResult(PassRefPtr<InspectorArray> nodeIds)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("addNodesToSearchResult");
    arguments->push(nodeIds);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::attributesUpdated(long id, PassRefPtr<InspectorArray> attributes)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("attributesUpdated");
    arguments->pushNumber(id);
    arguments->push(attributes);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::childNodeCountUpdated(long id, int newValue)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("childNodeCountUpdated");
    arguments->pushNumber(id);
    arguments->pushNumber(newValue);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::childNodeInserted(long parentId, long prevId, PassRefPtr<InspectorObject> node)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("childNodeInserted");
    arguments->pushNumber(parentId);
    arguments->pushNumber(prevId);
    arguments->push(node);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::childNodeRemoved(long parentId, long id)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("childNodeRemoved");
    arguments->pushNumber(parentId);
    arguments->pushNumber(id);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::setChildNodes(long parentId, PassRefPtr<InspectorArray> nodes)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("setChildNodes");
    arguments->pushNumber(parentId);
    arguments->push(nodes);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::setDetachedRoot(PassRefPtr<InspectorObject> root)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("setDetachedRoot");
    arguments->push(root);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::setDocument(PassRefPtr<InspectorValue> root)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("setDocument");
    arguments->push(root);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didStoreLastActivePanel(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didStoreLastActivePanel");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSaveApplicationSettings(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSaveApplicationSettings");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSaveSessionSettings(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSaveSessionSettings");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didEnableSearchingForNode(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didEnableSearchingForNode");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didDisableSearchingForNode(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didDisableSearchingForNode");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didEnableMonitoringXHR(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didEnableMonitoringXHR");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didDisableMonitoringXHR(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didDisableMonitoringXHR");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didEnableResourceTracking(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didEnableResourceTracking");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didDisableResourceTracking(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didDisableResourceTracking");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetResourceContent(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetResourceContent");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didReloadPage(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didReloadPage");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didStartTimelineProfiler(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didStartTimelineProfiler");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didStopTimelineProfiler(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didStopTimelineProfiler");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSetInjectedScriptSource(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSetInjectedScriptSource");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didDispatchOnInjectedScript(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didDispatchOnInjectedScript");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didAddScriptToEvaluateOnLoad(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didAddScriptToEvaluateOnLoad");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didRemoveAllScriptsToEvaluateOnLoad(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didRemoveAllScriptsToEvaluateOnLoad");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetChildNodes(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetChildNodes");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didApplyDomChange(long callId, bool success)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didApplyDomChange");
    arguments->pushNumber(callId);
    arguments->pushBool(success);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSetTextNodeValue(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSetTextNodeValue");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetEventListenersForNode(long callId, long nodeId, PassRefPtr<InspectorArray> listenersArray)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetEventListenersForNode");
    arguments->pushNumber(callId);
    arguments->pushNumber(nodeId);
    arguments->push(listenersArray);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didCopyNode(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didCopyNode");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didRemoveNode(long callId, long nodeId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didRemoveNode");
    arguments->pushNumber(callId);
    arguments->pushNumber(nodeId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didChangeTagName(long callId, long nodeId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didChangeTagName");
    arguments->pushNumber(callId);
    arguments->pushNumber(nodeId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetOuterHTML(long callId, const String& outerHTML)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetOuterHTML");
    arguments->pushNumber(callId);
    arguments->pushString(outerHTML);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSetOuterHTML(long callId, long nodeId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSetOuterHTML");
    arguments->pushNumber(callId);
    arguments->pushNumber(nodeId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didAddInspectedNode(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didAddInspectedNode");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didPerformSearch(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didPerformSearch");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSearchCanceled(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSearchCanceled");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didPushNodeByPathToFrontend(long callId, long nodeId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didPushNodeByPathToFrontend");
    arguments->pushNumber(callId);
    arguments->pushNumber(nodeId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didClearConsoleMessages(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didClearConsoleMessages");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didHighlightDOMNode(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didHighlightDOMNode");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didHideDOMNodeHighlight(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didHideDOMNodeHighlight");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetStyles(long callId, PassRefPtr<InspectorValue> styles)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetStyles");
    arguments->pushNumber(callId);
    arguments->push(styles);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetAllStyles(long callId, PassRefPtr<InspectorArray> styles)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetAllStyles");
    arguments->pushNumber(callId);
    arguments->push(styles);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetInlineStyle(long callId, PassRefPtr<InspectorValue> style)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetInlineStyle");
    arguments->pushNumber(callId);
    arguments->push(style);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetComputedStyle(long callId, PassRefPtr<InspectorValue> style)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetComputedStyle");
    arguments->pushNumber(callId);
    arguments->push(style);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetStyleSheet(long callId, PassRefPtr<InspectorValue> styleSheet)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetStyleSheet");
    arguments->pushNumber(callId);
    arguments->push(styleSheet);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetRuleRangesForStyleSheetId(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetRuleRangesForStyleSheetId");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didApplyStyleText(long callId, bool success, PassRefPtr<InspectorValue> style, PassRefPtr<InspectorArray> changedProperties)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didApplyStyleText");
    arguments->pushNumber(callId);
    arguments->pushBool(success);
    arguments->push(style);
    arguments->push(changedProperties);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSetStyleText(long callId, bool success)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSetStyleText");
    arguments->pushNumber(callId);
    arguments->pushBool(success);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSetStyleProperty(long callId, bool success)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSetStyleProperty");
    arguments->pushNumber(callId);
    arguments->pushBool(success);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didToggleStyleEnabled(long callId, PassRefPtr<InspectorValue> style)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didToggleStyleEnabled");
    arguments->pushNumber(callId);
    arguments->push(style);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSetRuleSelector(long callId, PassRefPtr<InspectorValue> rule, bool selectorAffectsNode)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSetRuleSelector");
    arguments->pushNumber(callId);
    arguments->push(rule);
    arguments->pushBool(selectorAffectsNode);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didAddRule(long callId, PassRefPtr<InspectorValue> rule, bool selectorAffectsNode)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didAddRule");
    arguments->pushNumber(callId);
    arguments->push(rule);
    arguments->pushBool(selectorAffectsNode);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetCookies(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetCookies");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didDeleteCookie(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didDeleteCookie");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetApplicationCaches(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetApplicationCaches");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didReleaseWrapperObjectGroup(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didReleaseWrapperObjectGroup");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didDidEvaluateForTestInFrontend(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didDidEvaluateForTestInFrontend");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetDatabaseTableNames(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetDatabaseTableNames");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didGetDOMStorageEntries(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didGetDOMStorageEntries");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didSetDOMStorageItem(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didSetDOMStorageItem");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}

void RemoteInspectorFrontend::didRemoveDOMStorageItem(long callId)
{
    RefPtr<InspectorArray> arguments = InspectorArray::create();
    arguments->pushString("didRemoveDOMStorageItem");
    arguments->pushNumber(callId);
    m_inspectorClient->sendMessageToFrontend(arguments->toJSONString());
}


} // namespace WebCore

#endif // ENABLE(INSPECTOR)
