import bb.cascades 1.2

Page {
    Container{
        
        layout: DockLayout {
        
        }
        horizontalAlignment: HorizontalAlignment.Center
        background: Color.create("#33b2e3")
        Container {
            
            verticalAlignment: VerticalAlignment.Center
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            
            }

            horizontalAlignment: HorizontalAlignment.Center
            preferredWidth: 600.0
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                
                }
                horizontalAlignment: HorizontalAlignment.Center
                
                verticalAlignment: VerticalAlignment.Bottom
                ImageView {
                    imageSource: "asset:///images/action_icon.png"
                }
                Label {
                    text: "FlippIt"
                    textStyle.color: Color.create("#FFFFFF")
                    textStyle.fontSizeValue: 0.0
                    textStyle.fontStyle: FontStyle.Default
                    textFit.minFontSizeValue: 20.0
                    textFit.maxFontSizeValue: 20.0
                    verticalAlignment: VerticalAlignment.Center
                }
            }
            Label {
            text: "To begin, download the FlippIt Chrome extension to communicate between your phone and your computer. 
            
The link has been emailed to you. "
                textStyle.color: Color.create("#FFFFFF")
                topMargin: 80.0
                multiline: true

            }
            Container {
                layout: DockLayout {

                }
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 60.0
                ImageView {
                    imageSource: "asset:///images/computer_white.png"
                    preferredHeight: 200
                    preferredWidth: 200
                    horizontalAlignment: HorizontalAlignment.Left
                }
                ImageView {
                    imageSource: "asset:///images/doublearrows_white.png"
                    preferredHeight: 200
                    preferredWidth: 200
                    horizontalAlignment: HorizontalAlignment.Center
                }
                ImageView {
                    imageSource: "asset:///images/phone_white.png"
                    preferredHeight: 200
                    preferredWidth: 200
                    horizontalAlignment: HorizontalAlignment.Right

                }
            
            }   
            Button {
                 id: welcome
                 text: "Continue"
                 onClicked: {
                    _app.openHistoryPage() 
                 }
                horizontalAlignment: HorizontalAlignment.Center
                topMargin: 60.0
            }
        
        }
    }
}
