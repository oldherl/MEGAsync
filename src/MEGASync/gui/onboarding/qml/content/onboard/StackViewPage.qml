// System
import QtQml 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

// QML common
import Common 1.0
import Components 1.0 as Custom

//Local
import Onboarding 1.0
import Onboard 1.0

Rectangle {
    id: root
    
    readonly property string normalStatus: "normal"
    readonly property string logInStatus: "login"
    readonly property string signUpStatus: "signUp"
    readonly property string fetchNodesStatus: "fetchNodes"
    readonly property string code2FAStatus: "twoFA"

    color: "transparent"
    state: normalStatus
    states: [
        State {
            name: normalStatus
            PropertyChanges {
                target: statusText
                visible: false
            }
            PropertyChanges {
                target: root
                enabled: true
            }
        },
        State {
            name: logInStatus
            PropertyChanges {
                target: statusText
                text: OnboardingStrings.statusLogin
                visible: true
            }
            PropertyChanges {
                target: root
                enabled: false
            }
        },
        State {
            name: signUpStatus
            PropertyChanges {
                target: statusText
                text: OnboardingStrings.statusSignUp
                visible: true
            }
            PropertyChanges {
                target: root
                enabled: false
            }
        },
        State {
            name: fetchNodesStatus
            PropertyChanges {
                target: statusText
                text: OnboardingStrings.statusFetchNodes
                visible: true
            }
            PropertyChanges {
                target: root
                enabled: false
            }
        },
        State {
            name: code2FAStatus
            PropertyChanges {
                target: statusText
                text: OnboardingStrings.status2FA
                visible: true
            }
            PropertyChanges {
                target: root
                enabled: false
            }
        }
    ]

    Custom.SecondaryText {
        id: statusText

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: root.bottom
            bottomMargin: 16
        }
        font.pixelSize: Custom.Text.Size.Small
    }

}
