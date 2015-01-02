import bb.cascades 1.2
import bb.cascades.pickers 1.0

Page {
    objectName: "sendPage"
    Container {
        ScrollView {
            scrollViewProperties.scrollMode: ScrollMode.Horizontal
            horizontalAlignment: HorizontalAlignment.Center   
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
            id: messageText
            objectName: "messageText"
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
                    filePicker.open()
                }
                imageSource: "asset:///images/upload_blue.png"
            }
            Button {
                objectName: "saveButton"
                text: "Save"
                imageSource: "asset:///images/onetime_blue.png"
                onClicked: {
                    _send.setSaveMessage()
                }
            }
            Button {
                text: "Clear"
                imageSource: "asset:///images/clear_blue.png"
            }
            attachedObjects: FilePicker {
                property string selectedFile
                id: filePicker
                title: "Select File"
                onFileSelected: {
                    selectedFile = selectedFiles[0]
                    fileText.text="file://"+selectedFile
                    //fileImage.imageSource="file://"+selectedFile
                    //fileImage.imageSource="asset:///images/clear_blue.png"
                    _send.filePicker(selectedFile)
                    
                }
            }
            horizontalAlignment: HorizontalAlignment.Center

        }
        Label {
            id:fileText
            objectName: "fileText"
        }
        ImageView {
            id:fileImage
            //imageSource: "file://accounts/1000/shared/downloads/images.jpg"
            objectName: "fileImage"
        }
        
    }
}
