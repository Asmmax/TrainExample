@echo off
cd %~dp0/../../
if not exist .venv (
	call scripts/win/setup_venv.bat
)
call .venv/Scripts/activate
echo Generator launch
cd %~dp0/../../deps/DIAssets/DIAssets/utils/generator
python generate.py %1 %2 %3 --in_dir=%in_dir%  --out_include_dir=%out_include_dir% --out_source_dir=%out_source_dir% --add_includes=%add_includes% --cache_path=%cache_path% --extra_cache_paths=%extra_cache_paths%
