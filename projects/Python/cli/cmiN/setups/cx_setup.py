from cx_Freeze import setup, Executable

executables = [
    Executable(
        script="source.py",
        initScript=None,
        base='Console', # Win32GUI
        compress=True,
        appendScriptToExe=True,
        appendScriptToLibrary=False,
        icon=None,
        copyDependentFiles=True
    )
]

setup(
    version="1.0",
    description="Some description.",
    author="Me",
    name="Soft",
    options=
    {
        "build_exe":
        {
            "optimize": 2,
            "compressed": True,
            "create_shared_zip": False,
            "include_in_shared_zip": False,
            "append_script_to_exe": True,
            "copy_dependent_files": True
        }
    },
    executables=executables
)
