import QtQuick 2.0

Rectangle {
  color: Style.currentTheme.primary

  Repeater{
      model: frameModel
      Rectangle{
          id: photoFrame
          width: 50
          height: 50
          Image {
              id: image
              anchors.centerIn: parent
              fillMode: Image.PreserveAspectFit
              source: frame
              antialiasing: true
          }

      }
  }

}
