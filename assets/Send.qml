import bb.cascades 1.2

Page {
    Container {
        ScrollView {
            scrollViewProperties.scrollMode: ScrollMode.Horizontal

            Container {
                objectName: "deviceContainer"
                layoutProperties: StackLayoutProperties {

                }
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                
                
                
                
            }

        }
        TextArea {
            id:messageText
            hintText: "Type your text here."
            maximumLength: 500
            preferredHeight: 200.0
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight

            }
            Button {
                text: "File"
                onClicked: {
                    _settings.filePicker();
                }
            }
            Button {
                text: "Save"
                
            }
            Button {
                text: "Clear"
            }
        }
    }
    onCreationCompleted: {
        _app.getDevices()
    }
}
