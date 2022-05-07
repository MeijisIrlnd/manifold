/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   MixerHandle_png;
    const int            MixerHandle_pngSize = 2512;

    extern const char*   MuteOff_png;
    const int            MuteOff_pngSize = 1443;

    extern const char*   MuteOn_png;
    const int            MuteOn_pngSize = 1442;

    extern const char*   PanText_png;
    const int            PanText_pngSize = 292;

    extern const char*   RotaryHandle_png;
    const int            RotaryHandle_pngSize = 1147;

    extern const char*   SoloOff_png;
    const int            SoloOff_pngSize = 1458;

    extern const char*   SoloOn_png;
    const int            SoloOn_pngSize = 1456;

    extern const char*   artyslider_jpg;
    const int            artyslider_jpgSize = 167927;

    extern const char*   Play_svg;
    const int            Play_svgSize = 191;

    extern const char*   Stop_svg;
    const int            Stop_svgSize = 1219;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
