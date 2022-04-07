if is_os("windows") then
    set_runtimes("MD")
end

option("package_manager")
    set_showmenu(true)
    if is_os("windows") then
        set_default("conan")
    else
        set_default("system")
    end
    set_values("system", "conan", "vcpkg")
option_end()

if is_config("package_manager", "system") then
    add_requires("sdl2", { alias = "sdl2" })
    add_requires("sdl2_image", { alias = "sdl2_image" })
    add_requires("sdl2_ttf", { alias = "sdl2_ttf" })
    add_requires("libnoise", { alias = "libnoise" })
    add_requires("openal", { alias = "openal" })
    add_requires("vorbis", { alias = "vorbis" })
    add_requires("angelscript", { alias = "angelscript", optional = true })
elseif is_config("package_manager", "conan") then
    add_requires("conan::sdl/2.0.20", { alias = "sdl2" })
    add_requires("conan::sdl_image/2.0.5", { alias = "sdl2_image" })
    add_requires("conan::sdl_ttf/2.0.18", { alias = "sdl2_ttf" })
    add_requires("conan::libnoise/1.0.0", { alias = "libnoise" })
    add_requires("conan::openal/1.19.1", { alias = "openal" })
    add_requires("conan::vorbis/1.3.7", { alias = "vorbis" })
    add_requires("conan::angelscript/2.35.1", { alias = "angelscript", optional = true })
elseif is_config("package_manager", "vcpkg") then
    add_requires("vcpkg::sdl", { alias = "sdl2" })
    add_requires("vcpkg::sdl_image", { alias = "sdl2_image" })
    add_requires("vcpkg::sdl_ttf", { alias = "sdl2_ttf" })
    add_requires("vcpkg::libnoise", { alias = "libnoise" })
    add_requires("vcpkg::openal", { alias = "openal" })
    add_requires("vcpkg::vorbis", { alias = "vorbis" })
    add_requires("vcpkg::angelscript", { alias = "angelscript", optional = true })
end

add_rules("mode.debug", "mode.release")

target("Cytopia")
    set_kind("binary")
    set_languages("c++17")
    add_files(
            "src/main.cxx",
            "src/Game.cxx",
            "src/engine/basics/Camera.cxx",
            "src/engine/basics/GameStates.cxx",
            "src/engine/basics/isoMath.cxx",
            "src/engine/basics/mapEdit.cxx",
            "src/engine/basics/PointFunctions.cxx",
            "src/engine/basics/Settings.cxx",
            "src/engine/basics/utils.cxx",
            "src/engine/Engine.cxx",
            "src/engine/EventManager.cxx",
            "src/engine/GameObjects/MapNode.cxx",
            "src/engine/Map.cxx",
            "src/engine/map/MapLayers.cxx",
            "src/engine/map/TerrainGenerator.cxx",
            "src/engine/ResourcesManager.cxx",
            "src/engine/Sprite.cxx",
            "src/engine/TileManager.cxx",
            "src/engine/ui/basics/ButtonGroup.cxx",
            "src/engine/ui/basics/Layout.cxx",
            "src/engine/ui/basics/UIElement.cxx",
            "src/engine/ui/widgets/Bar.cxx",
            "src/engine/ui/widgets/Button.cxx",
            "src/engine/ui/widgets/Checkbox.cxx",
            "src/engine/ui/widgets/Combobox.cxx",
            "src/engine/ui/widgets/Frame.cxx",
            "src/engine/ui/widgets/Image.cxx",
            "src/engine/ui/widgets/Slider.cxx",
            "src/engine/ui/widgets/Text.cxx",
            "src/engine/ui/widgets/TextField.cxx",
            "src/engine/ui/widgets/Tooltip.cxx",
            "src/engine/UIManager.cxx",
            "src/engine/WindowManager.cxx",
            "src/game/GamePlay.cxx",
            "src/game/ZoneManager.cxx",
            "src/services/GameClock.cxx",
            "src/services/Randomizer.cxx",
            "src/services/ResourceManager.cxx",
            "src/util/Exception.cxx",
            "src/util/Filesystem.cxx",
            "src/util/desktop/Filesystem.cxx",
            "src/util/LOG.cxx",
            "src/engine/audio/Soundtrack.cxx",
            "src/services/AudioMixer.cxx"
    )
    add_includedirs(
            "external/header_only",
            "src/engine",
            "src/engine/basics",
            "src/engine/common",
            "src/engine/GameObjects",
            "src/engine/map",
            "src/engine/ui/basics",
            "src/engine/ui/widgets",
            "src/engine/ui/menuGroups",
            "src/util"
    )
    add_defines("USE_AUDIO", "VERSION=\"Cytopia 2000 - Urban Update\"")
    add_packages(
            "sdl2", "sdl2_image", "sdl2_ttf", "libnoise", "openal", "vorbis", "angelscript"
    )
    if is_os("windows") then
        add_defines("WIN32")
        add_links(
                "dbghelp",
                "user32",
                "gdi32",
                "winmm",
                "imm32",
                "ole32",
                "oleaut32",
                "version",
                "uuid",
                "advapi32",
                "setupapi",
                "shell32"
        )
    end
    if has_package("angelscript") then
        add_defines("USE_ANGELSCRIPT")
        add_includedirs("external/as_add_on")
        add_files(
                "external/as_add_on/scriptbuilder/scriptbuilder.cpp",
                "external/as_add_on/scriptstdstring/scriptstdstring.cpp",
                "src/Scripting/ScriptEngine.cxx"
        )
    end
target_end()