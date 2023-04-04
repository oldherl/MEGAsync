import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

SyncsPage {

    property alias buttonGroup: buttonGroup

    ColumnLayout {
        spacing: 12
        width: 488
        anchors.leftMargin: 32
        anchors.left: parent.left

        Header {
            title: qsTr("Choose how you want to use MEGA")
            description: qsTr("Choose a installation type")
            Layout.preferredWidth: parent.width
            Layout.topMargin: 32
        }

        ButtonGroup {
            id: buttonGroup
        }

        ColumnLayout {
            spacing: 20
            Layout.topMargin: 20

            InstallationTypeButton {
                id: syncButton

                title: qsTr("Sync")
                description: qsTr("Sync your files between your computers with MEGA cloud, any change from one side will apply to another side.")
                imageSource: "../../../../../images/Onboarding/sync.svg"
                type: InstallationTypeButton.Type.Sync
                ButtonGroup.group: buttonGroup
            }

            InstallationTypeButton {
                id: backupsButton

                title: qsTr("Backup")
                description: qsTr("Automatically update your files from your computers to MEGA cloud. Files in your computer won’t be affected by the cloud.")
                imageSource: "../../../../../images/Onboarding/cloud.svg"
                type: InstallationTypeButton.Type.Backup
                ButtonGroup.group: buttonGroup
            }

            InstallationTypeButton {
                id: fuseButton

                title: qsTr("Fuse")
                description: qsTr("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.")
                imageSource: "../../../../../images/Onboarding/fuse.svg"
                type: InstallationTypeButton.Type.Fuse
                ButtonGroup.group: buttonGroup
            }
        }
    }

}
