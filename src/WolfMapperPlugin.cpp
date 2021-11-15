#include "DistrhoPlugin.hpp"
#include "extra/Mutex.hpp"
#include "extra/ScopedPointer.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Graph.hpp"
#include "Mathf.hpp"
#include "Oversampler.hpp"
#include "ParamSmooth.hpp"
#include "WolfMapperParameters.hpp"

#include "DspFilters/Dsp.h"

START_NAMESPACE_DISTRHO

class WolfMapper : public Plugin
{
public:
    WolfMapper()
        : Plugin(paramCount, 0, 1)
    {
    }

protected:
    const char *getLabel() const noexcept override
    {
        return "Wolf Mapper";
    }

    const char *getDescription() const noexcept override
    {
        return "MIDI CC remapping tool.";
    }

    const char *getMaker() const noexcept override
    {
        return "Wolf Plugins";
    }

    const char *getHomePage() const noexcept override
    {
        return "https://github.com/wolf-plugins/wolf-mapper";
    }

    const char *getLicense() const noexcept override
    {
        return "GPL v3+";
    }

    uint32_t getVersion() const noexcept override
    {
        return d_version(1, 0, 0);
    }

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('W', 'o', 'M', 'p');
    }

    void initParameter(uint32_t index, Parameter &parameter) override
    {
        if (index >= paramCount)
            return;

        switch (index)
        {
        case paramOut:
            parameter.name = "Out";
            parameter.symbol = "out";
            parameter.hints = kParameterIsOutput;
            parameter.ranges.def = 0.0f;
            break;
        }

        parameters[index] = parameter.ranges.def;
    }

    float getParameterValue(uint32_t index) const override
    {
        return parameters[index];
    }

    void setParameterValue(uint32_t index, float value) override
    {
        parameters[index] = value;
    }

    void initState(uint32_t index, String &stateKey, String &defaultStateValue) override
    {
        switch (index)
        {
        case 0:
            stateKey = "graph";
            break;
        }

        //generated with fprintf(stderr, "%A,%A,%A,%d;%A,%A,%A,%d;\n", 0.0f, 0.0f, 0.0f, wolf::CurveType::Exponential, 1.0f, 1.0f, 0.0f, wolf::CurveType::Exponential);
        defaultStateValue = String("0x0p+0,0x0p+0,0x0p+0,0;0x1p+0,0x1p+0,0x0p+0,0;");
    }

    void setState(const char *key, const char *value) override
    {
        const MutexLocker cml(mutex);

        if (std::strcmp(key, "graph") == 0)
        {
            tempLineEditor.rebuildFromString(value);
            mustCopyLineEditor = true;
        }
    }

    void run(const float **input, float **output, uint32_t frames,
                     const MidiEvent* midiEvents, uint32_t midiEventCount) override
    {
        const auto lockSucceeded = mutex.tryLock();

        if (lockSucceeded)
        {
            if (mustCopyLineEditor)
            {
                lineEditor = tempLineEditor;

                for (int i = 0; i < lineEditor.getVertexCount(); ++i)
                {
                    lineEditor.getVertexAtIndex(i)->setGraphPtr(&lineEditor);
                }

                mustCopyLineEditor = false;
            }
        }

        for (uint32_t i = 0; i < midiEventCount; ++i)
        {
            const auto *event = &midiEvents[i];

            if (event->data[0] == 0xB0) // midi cc
            {
                const uint8_t inCC = event->data[2];                
                const float normalizedInCC = wolf::clamp(static_cast<float>(inCC) / 128.f, 0.f, 1.f);
                setParameterValue(paramOut, normalizedInCC);

                const auto normalizedOutCC = lineEditor.getValueAt(normalizedInCC);
                const auto outCC = static_cast<uint8_t>(normalizedOutCC * 128.f);

                auto newEvent = MidiEvent();
                newEvent.data[0] = 0xB0;
                newEvent.data[1] = event->data[1];
                newEvent.data[2] = outCC;

                if (!writeMidiEvent(newEvent))
                {
                    break;
                }
            }
        }

        if (lockSucceeded)
        {
            mutex.unlock();
        }
    }

private:
    float parameters[paramCount];

    wolf::Graph lineEditor;
    wolf::Graph tempLineEditor;
    bool mustCopyLineEditor = false;

    Mutex mutex;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WolfMapper)
};

Plugin *createPlugin()
{
    return new WolfMapper();
}

END_NAMESPACE_DISTRHO
