import QtQuick
import QtQuick.Window
import QtQuick.Controls

Item {
	id: item

	Connections {
        target: myClass
		ignoreUnknownSignals: true
        function onValueChanged(v) {
			console.log("C++ value: " + v)
		}
    }
}