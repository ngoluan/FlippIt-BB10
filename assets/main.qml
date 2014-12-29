/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2
NavigationPane {
    id:navPane
    objectName: "navPane"
   
    Page {
        Container {
            id: mainView
            
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            layout: DockLayout {

            }
            layoutProperties: AbsoluteLayoutProperties {

            }

            
            ListView {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Top
                dataModel: _history.model
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        HistoryItem {
                            id:historyitem
                            message: ListItemData.message
                            dateTime: ListItemData.dateTime
                            contextActions: [
                                ActionSet {
                                    actions: [
                                        ActionItem {
                                            title: "Copy"
                                            onTriggered: {
                                                //_app.createToast("testmessage");
                                                //_app.copyItem(ListItemData.message);
                                                historyitem.ListItem.view.copyItem("test")      
                                            }
                                            
                                        },
                                        ActionItem {
                                            title: "Open"
                                        },
                                        ActionItem {
                                            title: "Share"
                                            onTriggered: {
                                                invokeQuery.mimeType = "text/plain"
                                                invokeQuery.data = "mytext";
                                                invokeQuery.updateQuery();
                                            }
                                        },
                                        ActionItem {
                                            title: "Send"
                                            onTriggered: {
                                                var page = sendPage.createObject();
                                                page.messageText.text="test message"
                                                navPane.push(page)
                                            }
                                        }
                                    ]
                                } // end of ActionSet
                            ] // end of contextActions list
                        }
                    }
                
                ]
                function copyItem(message){
                    _app.copyItem(message);
                }
                
                onCreationCompleted: {
                    _app.getHistory();
                    //_history.addData();
                }
                
            }
            
            ImageButton {
                id: sendButton
                defaultImageSource: "asset:///images/sendbutton.png"
                preferredWidth: 128.0
                preferredHeight: 128.0
                layoutProperties: AbsoluteLayoutProperties {
                
                }
                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Center
                bottomMargin: 40.0
                onClicked: {
                    var page = sendPage.createObject();
                    navPane.push(page)
                }
            }
            
        }

    }
    attachedObjects: [
        ComponentDefinition {
            id: sendPage
            
            source: "Send.qml"
        },
        Invocation {
           id: invokeShare
           query: InvokeQuery {
               id:invokeQuery
               mimeType: "text/plain"                        
           }
           onArmed: {
               if (invokeQuery.data != "") {
                   trigger("bb.action.SHARE");
               }
           }             
        }
    ]
    onPushTransitionEnded: {
        if(navPane.top.objectName=="sendPage")
        {
            _app.getDevices()
        }
        //if(navPane.top.objectName)
    }
}


