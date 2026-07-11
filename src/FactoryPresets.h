#include "Presets.h"

namespace presets {

static const char* const mdaPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="0.0"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="80.3"/>
    <PARAM id="velocityToMuffling" value="25.1"/>
    <PARAM id="velocitySensitivity" value="37.6"/>
    <PARAM id="stereoWidth" value="100.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.246"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const plainPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="0.0"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="75.1"/>
    <PARAM id="velocityToMuffling" value="0.0"/>
    <PARAM id="velocitySensitivity" value="45.2"/>
    <PARAM id="stereoWidth" value="0.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.0"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const compressedPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="90.2"/>
    <PARAM id="envRelease" value="39.9"/>
    <PARAM id="hardness" value="12.03"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="100.0"/>
    <PARAM id="velocityToMuffling" value="33.1"/>
    <PARAM id="velocitySensitivity" value="29.9"/>
    <PARAM id="stereoWidth" value="99.8"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.0"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const dancePiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="39.9"/>
    <PARAM id="envRelease" value="25.1"/>
    <PARAM id="hardness" value="50.0"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="67.2"/>
    <PARAM id="velocityToMuffling" value="12.4"/>
    <PARAM id="velocitySensitivity" value="12.7"/>
    <PARAM id="stereoWidth" value="49.8"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.283"/>
    <PARAM id="stretchTuning" value="16.7"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const concertPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="64.8"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="0.0"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="29.8"/>
    <PARAM id="velocityToMuffling" value="60.2"/>
    <PARAM id="velocitySensitivity" value="55.0"/>
    <PARAM id="stereoWidth" value="170.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.339"/>
    <PARAM id="stretchTuning" value="16.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="20.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const darkPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="60.2"/>
    <PARAM id="hardness" value="-50.0"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="30.4"/>
    <PARAM id="velocityToMuffling" value="20.0"/>
    <PARAM id="velocitySensitivity" value="33.6"/>
    <PARAM id="stereoWidth" value="130.2"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.317"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const schoolPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="45.0"/>
    <PARAM id="envRelease" value="59.8"/>
    <PARAM id="hardness" value="12.6"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="60.3"/>
    <PARAM id="velocityToMuffling" value="50.0"/>
    <PARAM id="velocitySensitivity" value="17.4"/>
    <PARAM id="stereoWidth" value="66.2"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.421"/>
    <PARAM id="stretchTuning" value="30.1"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="40.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const brokenPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="0.0"/>
    <PARAM id="envDecay" value="5.0"/>
    <PARAM id="envRelease" value="95.7"/>
    <PARAM id="hardness" value="0.0"/>
    <PARAM id="velocityToHardness" value="50.0"/>
    <PARAM id="mufflingFilter" value="29.9"/>
    <PARAM id="velocityToMuffling" value="100.0"/>
    <PARAM id="velocitySensitivity" value="0.0"/>
    <PARAM id="stereoWidth" value="100.0"/>
    <PARAM id="fineTuning" value="-5.0"/>
    <PARAM id="randomDetuning" value="0.718"/>
    <PARAM id="stretchTuning" value="-50.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.0"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="0.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const defaultEPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="1.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="0.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.65"/>
    <PARAM id="velocitySensitivity" value="25.0"/>
    <PARAM id="stereoWidth" value="100.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.146"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="velocityToHardness" value="0.0"/>
    <PARAM id="mufflingFilter" value="0.0"/>
    <PARAM id="velocityToMuffling" value="50.0"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const brightEPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="1.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="50.0"/>
    <PARAM id="trebleBoost" value="30.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.65"/>
    <PARAM id="velocitySensitivity" value="25.0"/>
    <PARAM id="stereoWidth" value="100.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.146"/>
    <PARAM id="overdrive" value="50.0"/>
    <PARAM id="velocityToHardness" value="0.0"/>
    <PARAM id="mufflingFilter" value="0.0"/>
    <PARAM id="velocityToMuffling" value="50.0"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="40.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const mellowEPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="1.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="-50.0"/>
    <PARAM id="trebleBoost" value="-50.0"/>
    <PARAM id="modulation" value="0.5"/>
    <PARAM id="lfoRate" value="0.65"/>
    <PARAM id="velocitySensitivity" value="25.0"/>
    <PARAM id="stereoWidth" value="100.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.246"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="velocityToHardness" value="0.0"/>
    <PARAM id="mufflingFilter" value="0.0"/>
    <PARAM id="velocityToMuffling" value="50.0"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const autopanEPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="1.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="0.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.25"/>
    <PARAM id="lfoRate" value="0.65"/>
    <PARAM id="velocitySensitivity" value="25.0"/>
    <PARAM id="stereoWidth" value="100.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.246"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="velocityToHardness" value="0.0"/>
    <PARAM id="mufflingFilter" value="0.0"/>
    <PARAM id="velocityToMuffling" value="50.0"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="0.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

static const char* const tremoloEPiano = R"preset(
<?xml version="1.0" encoding="UTF-8"?>

<PRESET>
  <Parameters>
    <PARAM id="instrument" value="1.0"/>
    <PARAM id="envDecay" value="50.0"/>
    <PARAM id="envRelease" value="50.0"/>
    <PARAM id="hardness" value="0.0"/>
    <PARAM id="trebleBoost" value="0.0"/>
    <PARAM id="modulation" value="0.75"/>
    <PARAM id="lfoRate" value="0.65"/>
    <PARAM id="velocitySensitivity" value="25.0"/>
    <PARAM id="stereoWidth" value="100.0"/>
    <PARAM id="fineTuning" value="0.0"/>
    <PARAM id="randomDetuning" value="0.246"/>
    <PARAM id="overdrive" value="0.0"/>
    <PARAM id="velocityToHardness" value="0.0"/>
    <PARAM id="mufflingFilter" value="0.0"/>
    <PARAM id="velocityToMuffling" value="50.0"/>
    <PARAM id="stretchTuning" value="0.0"/>
    <PARAM id="reverbDamp" value="70.0"/>
    <PARAM id="reverbMix" value="90.0"/>
    <PARAM id="reverbSize" value="7.0"/>
    <PARAM id="outputLevel" value="-12.0"/>
  </Parameters>
</PRESET>
)preset";

}  // namespace presets
