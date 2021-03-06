# ☑ task
[![appveyor build](https://ci.appveyor.com/api/projects/status/rtl31pwna7xxcypb?svg=true)](https://ci.appveyor.com/project/mtso/task)
[![Issue Count](https://codeclimate.com/github/mtso/task/badges/issue_count.svg)](https://codeclimate.com/github/mtso/task/issues)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/56dc60ece47849829b1023582813d830)](https://www.codacy.com/app/mtso/task?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=mtso/task&amp;utm_campaign=Badge_Grade)
![supported platforms](https://img.shields.io/badge/platforms-win32-blue.svg?colorB=41b6e6)

Git-based collaborative project management.

## Description

Task is a project management tool run from the command line.
It allows team members to create and assign tasks. The data is
saved as a text file that can be pushed to any git server.

### Usage

The TaskApp.exe can be found in the bin/ folder.
Opening this directly will make it search for the .task directory in a sibling folder of path "..\\.task".
The task.cmd file in the top level will call the TaskApp.exe with an argument of --top-root,
which notifies the app to search for the .task directory in the top level path ".task".

## Information

- De Anza CIS 22C: Fall 2016
- Professor Manish Goel

### Team 一 (one)

- Adrian Marroquin
- Matthew Tso
- Xin He
- Jinzhu Shen
