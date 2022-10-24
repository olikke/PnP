pragma Singleton
import QtQuick 2.9

QtObject{

    property bool isDarkMode: currentTheme === darkTheme

    property int vvv

    function setDarkMode(value){ currentTheme =  value? darkTheme:lightTheme }

    function setStateColor(state){  
        switch(state){
        case 0: return Style.unitGreen;
            case 1: return Style.unitYellow;
                case 2: return Style.unitRed;
                    case 3: return Style.currentTheme.primary;
                        default: return Style.unitRed
        }
    }

    function setStateColorInfopanel(state){
        switch(state){
        case 0: return Style.unitGreen;
            case 1: return Style.unitYellow;
                case 2: return Style.unitRed;
                    case 3: return Qt.darker(Style.currentTheme.primary, 1.2);
                        default: return Style.unitRed
        }
    }

    //not sure can i combine this?
    function setFontColor(state,colorInvert){
        switch(state){
        case 0: return Style.unitGreen;
        case 1: return Style.unitYellow;
        case 2: return Style.unitRed;
        case 3: if (colorInvert) return Style.currentTheme.background;
            return Style.currentTheme.foreground;
        default: return Style.currentTheme.foreground;
        }
    }

    function stateToBool(state){
        return !(state > 0)
    }

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
    //property bool bordersEnabled: true // включение  линии границ контролов (ТЕСТОВАЯ)
    property bool rounded: true // включение закругления контролов (ТЕСТОВАЯ)
    property int animationDuration: 140
    property int unitRadius: 6 // общий радиус углов во всем Gui
    property int connectionWidth: 2 // толщина линий соединений между разъемами блоков на мнемосхемах
    property real controlsPrimaryColorDarkerValue: 1.4 // насколько затемняется праймари цвет в некоторых элементах (слайдер, свитч)
    property real disableControlsOpacity: 0.3 // коэффициент видимости ректангла наложенного на контролы, для затенения, когда контрол неактивен
    property real fadeOpacity: 0.92 // прозрачность панели затеняющей GUI при открытии настроек и страниц блоков
    property int topBarHeight: 36 // высота всех таббаров
    property int fieldHeight: 42 // высота полей некоторых компонентов (настройки и прочее)
    property int cardHeight: 62 // высота одинарной карточки (панели управления операторов)
    property int tableRowHeight: 32 //высота одной строки в таблице (для страниц устройств (TM-2221) и пр)
    property int smallCardHeight: cardHeight/2 // половина высоты одинарной карточки
    property int recordRedDotWidth: 9 // высота индикатора записи (панели управления АРМов)
    property color recordingBagroundColor: currentTheme.accent // цвет ректангла наложенного на основной, для отображения активности записи компонента (АРМЦ, АРММ, УВЗ2)
    property real recordBackgroundRectangleOpacity: 0.3 // прозрачность ректангла, цвет которому устанавливается выше, там же и обьяснение кто такой
    property real mnemonicConnectionOpacity: 0.3 // прозрачность соединений внутри коцевых корпусов до наведения
    property real tableValueWidth: 0.2 //ширина столбца значений для таблицы
    property int settingsWidth: 400 // ширина панели настроек
    property int scrollBarHeight: 10
    property int appWindowHeight: 0
    property int appWindowWidth: 0
    property int panelsMargins: 5 // отступы от всех сторон окна и расстояния между всем и вся в страницах блоков
    property int panelsSpacing: 10 // расстояние между панелями в страницах блоков
    property int blurRadius: 40
}

