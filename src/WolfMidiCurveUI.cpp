#include "DistrhoUI.hpp"

#include "Config.hpp"
#include "Margin.hpp"
#include "Window.hpp"
#include "WolfMidiCurveUI.hpp"

#include <string>

START_NAMESPACE_DISTRHO

WolfMidiCurveUI::WolfMidiCurveUI()
    : UI(611, 662)
{
    const uint minWidth = 611;
    const uint minHeight = 438;

    loadSharedResources();

    const float width = getWidth();
    const float height = getHeight();

    fGraphWidget = new GraphWidget(this, Size<uint>(width - 4 * 2, height - 4 * 2 - 122));

    const float graphBarHeight = 42;

    fGraphBar = new WidgetBar(this, Size<uint>(width, graphBarHeight));
    // fGraphBar->setStrokePaint();
    fGraphBar->setStrokeWidth(4.0f);

    fHandleResize = new ResizeHandle(this, Size<uint>(18, 18));
    fHandleResize->setCallback(this);
    fHandleResize->setMinSize(minWidth, minHeight);

    fButtonResetGraph = new ResetGraphButton(this, Size<uint>(32, 32));
    fButtonResetGraph->setCallback(this);

    fLabelButtonResetGraph = new NanoLabel(this, Size<uint>(50, fButtonResetGraph->getHeight()));
    fLabelButtonResetGraph->setText("RESET");
    // fLabelButtonResetGraph->setFontId(dejaVuSansId);
    fLabelButtonResetGraph->setFontSize(15.0f);
    fLabelButtonResetGraph->setAlign(ALIGN_LEFT | ALIGN_MIDDLE);
    fLabelButtonResetGraph->setMargin(Margin(6, 0, std::round(fButtonResetGraph->getHeight() / 2.0f) + 1, 0));

    positionWidgets(width, height);
}

WolfMidiCurveUI::~WolfMidiCurveUI()
{
}

void WolfMidiCurveUI::positionWidgets(uint width, uint height)
{
    //TODO: Clean that up

    const float graphMargin = 8;
    const float bottomBarSize = 102;
    const float graphBarHeight = fGraphBar->getHeight();
    const float graphBarMargin = 6;

    const float graphWidth = width - graphMargin * 2;
    const float graphHeight = height - graphMargin * 2 - bottomBarSize - graphBarHeight;
    const float graphBottom = graphMargin + graphHeight;

    fGraphWidget->setSize(graphWidth, graphHeight);
    fGraphWidget->setAbsolutePos(graphMargin, graphMargin);

    fGraphBar->setWidth(width);
    fGraphBar->setAbsolutePos(0, graphBottom + graphBarMargin);
    fGraphBar->setFillPaint(radialGradient(width / 2.0f, graphBarHeight / 2.0f, graphBarHeight, width / 2.0f, Color(71, 74, 80, 255), Color(40, 42, 46, 255)));

    const float graphBarMiddleY = fGraphBar->getAbsoluteY() + fGraphBar->getHeight() / 2.0f;

    fButtonResetGraph->setAbsolutePos(20, graphBarMiddleY - fButtonResetGraph->getHeight() / 2.0f);
    fLabelButtonResetGraph->setAbsolutePos(fButtonResetGraph->getAbsoluteX() + fButtonResetGraph->getWidth(), fButtonResetGraph->getAbsoluteY());

    fHandleResize->setAbsolutePos(width - fHandleResize->getWidth(), height - fHandleResize->getHeight());
}

void WolfMidiCurveUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case paramOut:
        fGraphWidget->updateInput(value);
        break;
    default:
        break;
    }
}

void WolfMidiCurveUI::stateChanged(const char *key, const char *value)
{
    if (std::strcmp(key, "graph") == 0)
        fGraphWidget->rebuildFromString(value);

    repaint();
}

void WolfMidiCurveUI::onNanoDisplay()
{
    const float width = getWidth();
    const float height = getHeight();

    //background
    beginPath();

    rect(0.f, 0.f, width, height);
    fillColor(WolfMidiCurveConfig::plugin_background);

    fill();

    closePath();

    //shadow at the bottom of the graph
    beginPath();

    const int shadowHeight = 8;
    const int shadowMargin = 2;

    const float graphMargin = 8;
    const float bottomBarSize = 102;
    const float graphBarHeight = fGraphBar->getHeight();

    const float graphHeight = height - graphMargin * 2 - bottomBarSize - graphBarHeight;
    const float graphBottom = graphMargin + graphHeight;

    const float shadowTop = graphBottom + shadowMargin;
    const float shadowBottom = shadowTop + shadowHeight;

    rect(0.0f, shadowTop, getWidth(), shadowHeight);

    Paint gradient = linearGradient(0, shadowTop, 0, shadowBottom, Color(21, 22, 30, 0), Color(21, 22, 30, 180));
    fillPaint(gradient);

    fill();

    closePath();
}

void WolfMidiCurveUI::uiIdle()
{
}

bool WolfMidiCurveUI::onMouse(const MouseEvent &ev)
{
    fGraphWidget->hideMenuOnMouseOut(ev.pos);
    return false;
}

bool WolfMidiCurveUI::onMotion(const MotionEvent &ev)
{
    fGraphWidget->hideMenuOnMouseOut(ev.pos);
    return false;
}

void WolfMidiCurveUI::uiReshape(uint width, uint height)
{
    //setSize(width, height);
    positionWidgets(width, height);
}

bool WolfMidiCurveUI::onKeyboard(const KeyboardEvent &)
{
    return true;
}

void WolfMidiCurveUI::nanoButtonClicked(NanoButton *nanoButton)
{
    if (nanoButton == fButtonResetGraph)
    {
        fGraphWidget->reset();
        return;
    }
}

void WolfMidiCurveUI::resizeHandleMoved(int width, int height)
{
    setSize(width, height);
}

UI *createUI()
{
    return new WolfMidiCurveUI();
}

END_NAMESPACE_DISTRHO
