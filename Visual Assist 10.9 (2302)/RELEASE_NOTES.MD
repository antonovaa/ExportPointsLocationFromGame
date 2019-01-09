# Release notes 2302

• **New!** Very preliminary support for `VS 2019 Preview 1`. Known issues: `VA Step Filter` does not work when `Load debug symbols in external process` is enabled (new VS feature, enabled by default); yellow bar notification regarding extension at risk of not functioning in a future VS update; changes expected in Preview 2 will almost certainly require another update of VA (build 2302 is unlikely to integrate properly with VC++ in Preview 2); preview instability has greatly impacted our ability to test VA in it. (case=132624) [16462](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=16462)

• **New!** Added support for UTF-8 encoding of dictionary files used by `Spell Check`. (case=132797)

• Fix for exception caught and reported by Visual Studio during startup when VA debugger integration is disabled (regression in 2301). (case=132716) [16465](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=16465)

• Fixes for `Spell Check` underlining and correction menu (regression in 2301). (case=132797)



# Changes in build 2301


• **New!** [VS2010+] [Beta] Support for shared solution-defined [Source Links](https://docs.wholetomato.com/default.asp?W754). (case=115282)

• **New!** [VS2015+] Added toggle command to *temporarily* bind all breakpoints to the current thread (`VAssistX | Debug | Bind Breakpoints to Current Thread`). (case=117963)

• **New!** [VS2015+] Added toggle command to *temporarily* disable all currently enabled breakpoints (`VAssistX | Debug | Skip All Breakpoints`). (case=117964)


• **New!** [VS2010+] `Source Links File Viewer` plugin renders SVG content. (case=119335) [16369](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=16369)

• Improved support of identifiers with non-ASCII characters. (case=500, case=2366, case=4983, case=5792, case=90174, case=105281)

• Improved support for UE4. (case=108835, case=116702, case=117768, case=119915, case=120043, case=131103, case=117081) [15248](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=15248), [15244](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=15244), [15240](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=15240), [15248](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=15248), [15226](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=15226)

• `Code Inspections` no longer offered in system include headers (restore previous behavior via `ExcludeSystemDirectories` registry value). (case=119565)

• `Code Inspections` no longer offered in third party source (restore previous behavior via `Exclude3rdPartyDirectories` registry value). (case=119844)

• [VS2017] Fix for incompatibility with `IntelliCode suggestions`. (case=118434) [15300](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=15300)

• [VS2010+] Fix for incorrect link generation by `Source Links File Viewer` plugin due to ignoring word boundaries. (case=118798)

• [VS2017 15.9+] Keyboard bindings for the Visual Assist `SmartSelectExtend` and `SmartSelectShrink` commands added to `Recommended Keyboard Shortcuts` dialog due to 15.9 now using the bindings for itself by default. (case=119816)

• Fix for incorrect code generation in some cases during quick fix for 'convert to range-based for loop.' (case=117328)

• Fix for items following block comments missing from `Methods In File` list in some cases. (case=131102)

• Fix for incorrect coloring of symbol after string literals that contain non-ASCII text on Windows 10 Insider Preview. (case=116803)

• Fix for incorrect creation status in `Find References` results window for extern variable declarations. (case=117634)

• Fix for failure to be able to use non-ASCII characters in `Rename Files` and `Create File` dialogs. (case=130729)

• Fix for `Rename Files` dialog defaulting to incorrect name in some scenarios. (case=130794)

• Fix for `Add Forward Declaration` being unavailable on parameter type when initializer list is present. (case=131036)

• Fix for `Add Include` producing incorrect path in some cases with the "Prefer path relative to project" option. (case=119905)

• Fix for improperly parented message boxes when using floating editor windows. (case=118459)

• Visual Assist version number now reported in About Visual Studio dialog. (case=120047) [16415](https://forums.wholetomato.com/forum/topic.asp?TOPIC_ID=16415)

