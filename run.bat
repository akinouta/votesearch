@echo on
cmake -G "MinGW Makefiles" -Bbuild -H . -DCMAKE_BUILD_TYPE=Debug
cmake --build build
mkdir bin\graph
set dataset=sift
set data_path=dataset\sift

@REM if not exist .\bin\graph\hcnng.ivecs (
    .\bin\test_build_index %data_path%\%dataset%_base.fvecs 1000 20 .\bin\graph\hcnng.ivecs
@REM )

@REM .\bin\test_ordinary_search %data_path%\%dataset%_base.fvecs %data_path%\%dataset%_query.fvecs %data_path%\%dataset%_groundtruth.ivecs .\bin\graph\hcnng.ivecs 1 -1
.\bin\test_2phase_search %data_path%\%dataset%_base.fvecs %data_path%\%dataset%_query.fvecs %data_path%\%dataset%_groundtruth.ivecs .\bin\graph\hcnng.ivecs 1 -1