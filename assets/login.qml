import bb.cascades 1.2

Page {
    id:loginPage
    objectName: "loginPage"
    Container{
        opacity: 1.0
        layout: DockLayout {

        }
        background: Color.create("#33b2e3")
        Container {

            verticalAlignment: VerticalAlignment.Center
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom

            }
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
            Container {
                background: Color.create("#FFFFFF")
                topPadding: 20.0
                leftPadding: 20.0
                bottomPadding: 20.0
                rightPadding: 20.0
                verticalAlignment: VerticalAlignment.Top
                horizontalAlignment: HorizontalAlignment.Center
                topMargin: 20
                Label {
                    text: "Please login or register"

                }
                TextField {
                    id: emailText
                    objectName: "emailText"
                    hintText: "email@address.com"
                    inputMode: TextFieldInputMode.EmailAddress

                }
                TextField {
                    id: passwordText
                    objectName: "passwordText"
                    hintText: "password"
                    inputMode: TextFieldInputMode.Password

                }
                Container {
                    id: containerID
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        id:loginButton
                        text: "Login"
                        onClicked: {
                            _app.login()
                        }
                    }
                    Button {
                        id: registerButton
                        text: "Register"
                    }
                }

            }
        }
    }
}
