pragma Singleton
import QtQuick 2.9

QtObject{

    property bool isDarkMode: currentTheme === darkTheme

    function setDarkMode(value){ currentTheme =  value? darkTheme:lightTheme }

    property var currentTheme: darkTheme

    property var darkTheme:{
        "background": "#2f2f2f",
        "primary": "#464646",
        "accent": "#039be5",
        "foreground": "#f7f7f7",
        "fadeColor": Qt.darker("#2f2f2f", 2)
    }

    property var lightTheme:{
        "background":  "#d9d9d9",
        "lightBackground": "#d9d9d9",
        "primary": "#e6e6e6",
        "accent": "#04a2f1",
        "foreground": "#333333",
        "fadeColor": Qt.darker("#d9d9d9", 2)
    }

    // FONTS
    property string robotoCondensed: regularFont.name
    property FontLoader regularFont: FontLoader { source: "qrc:/ASSETS/fonts/RobotoCondensed-Regular.otf" }

    // COLORS
    property color scrollbarColor: isDarkMode ? Qt.lighter(currentTheme.primary, 2) : Qt.darker(currentTheme.primary, 2)
    property color sidePanelDelegateColor: isDarkMode ? Qt.lighter(currentTheme.primary, 1.2) : currentTheme.background
    property color foregroundDark: lightTheme.foreground // Темный цвет шрифта, не зависит от темы
    property color unitRed: appConfig.darkTheme ? "#f34245" : "#e83034" // состояние блока: ОШИБКИ
    property color unitGreen: "#29e19a" // состояние блока: НЕТ ОШИБОК
    property color unitYellow: appConfig.darkTheme ? "#fdc934" : "#ff9900" // состояние блока: ЕСТЬ ЗАМЕЧАНИЯ

    // NUMERIC VARIABLES
    property bool rounded: true // включение закругления контролов (ТЕСТОВАЯ)
    property int animationDuration: 140
    property int unitRadius: 6 // общий радиус углов во всем Gui
    property int connectionWidth: 2 // толщина линий соединений между разъемами блоков на мнемосхемах
    property int topBarHeight: 36 // высота всех таббаров
    property int fieldHeight: 42 // высота полей некоторых компонентов (настройки и прочее)
    property int cardHeight: 62 // высота одинарной карточки (панели управления операторов)
    property int panelsMargins: 5 // отступы от всех сторон окна и расстояния между всем и вся в страницах блоков
    property int btnHeight: 42
    property int iconSize: btnHeight*0.8
    property int sidePanel: 350
}


