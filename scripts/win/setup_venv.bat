@echo off
cd %~dp0/../../
echo Install python env
python -m venv .venv
call .venv/Scripts/activate
echo Install packages
pip install libclang