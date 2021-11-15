#pragma once

#include "ArrowButton.hpp"
#include "BipolarModeSwitch.hpp"
#include "DistrhoUI.hpp"
#include "GlowingLabelsBox.hpp"
#include "GraphWidget.hpp"
#include "LabelBox.hpp"
#include "LabelBoxList.hpp"
#include "NanoLabel.hpp"
#include "OversampleWheel.hpp"
#include "RemoveDCSwitch.hpp"
#include "ResetGraphButton.hpp"
#include "ResizeHandle.hpp"
#include "VolumeKnob.hpp"
#include "WidgetBar.hpp"
#include "WolfMapperParameters.hpp"

START_NAMESPACE_DISTRHO

class WolfMapperUI : public UI,
                     public NanoButton::Callback,
                     public ResizeHandle::Callback
{
public:
    WolfMapperUI();
    ~WolfMapperUI();

    float getParameterValue(uint32_t index) const;

protected:
    void parameterChanged(uint32_t, float value) override;
    void tryRememberSize();
    void positionWidgets(uint width, uint height);

    void nanoButtonClicked(NanoButton *nanoButton) override;

    void resizeHandleMoved(int width, int height) override;

    void stateChanged(const char *key, const char *value) override;
    void onNanoDisplay() override;
    void uiIdle() override;
    void uiReshape(uint width, uint height) override;
    bool onKeyboard(const KeyboardEvent &ev) override;
    bool onMouse(const MouseEvent &ev) override;
    bool onMotion(const MotionEvent &ev) override;

private:
    ScopedPointer<ResizeHandle> fHandleResize;

    ScopedPointer<GraphWidget> fGraphWidget;
    ScopedPointer<WidgetBar> fGraphBar;
    ScopedPointer<ResetGraphButton> fButtonResetGraph;
    ScopedPointer<NanoLabel> fLabelButtonResetGraph;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WolfMapperUI)
};

END_NAMESPACE_DISTRHO
