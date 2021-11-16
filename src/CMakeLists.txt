dpf_add_plugin(wolf-midicurve
        TARGETS jack lv2 vst2
	FILES_DSP
		Utils/src/Mathf.cpp
		Structures/src/Graph.cpp 
		Structures/src/ParamSmooth.cpp 
		WolfMidiCurvePlugin.cpp
	FILES_UI
		Utils/src/Mathf.cpp 
		Structures/src/Graph.cpp 
		Structures/src/Margin.cpp 
		Structures/src/Animation.cpp 
		Widgets/src/WolfWidget.cpp 
		Widgets/src/GraphNode.cpp 
		Widgets/src/GraphWidget.cpp 
		Widgets/src/NanoSwitch.cpp 
		Widgets/src/RemoveDCSwitch.cpp 
		Widgets/src/NanoButton.cpp 
		Widgets/src/ResetGraphButton.cpp 
		Widgets/src/NanoWheel.cpp 
		Widgets/src/OversampleWheel.cpp 
		Widgets/src/NanoKnob.cpp 
		Widgets/src/VolumeKnob.cpp 
		Widgets/src/ResizeHandle.cpp 
		Widgets/src/LabelBox.cpp 
		Widgets/src/LabelBoxList.cpp 
		Widgets/src/BipolarModeSwitch.cpp 
		Widgets/src/LabelContainer.cpp 
		Widgets/src/GlowingLabelsBox.cpp 
		Widgets/src/NanoLabel.cpp 
		Widgets/src/WidgetBar.cpp 
		Widgets/src/ArrowButton.cpp 
		Widgets/src/MenuWidget.cpp
		Resources/Fonts/chivo_bold.cpp 
		Resources/Fonts/chivo_italic.cpp 
		WolfMidiCurveUI.cpp
)

target_include_directories(wolf-midicurve PUBLIC
	"."
	"../dpf/distrho"
	"../dpf/dgl"
	"./Structures"
	"./Widgets"
	"./Utils"
	"./Resources"
)

target_link_libraries(wolf-midicurve PUBLIC Threads::Threads)
