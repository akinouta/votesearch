@echo on
cmake -G "MinGW Makefiles" -Bbuild -H.
cmake --build build
mkdir bin\graph
set data_path=dataset\siftsmall

if not exist .\bin\graph\hcnng.ivecs (
    .\bin\test_build_index %data_path%\siftsmall_base.fvecs 1000 20 .\bin\graph\hcnng.ivecs
)

.\bin\test_ordinary_search %data_path%\siftsmall_base.fvecs %data_path%\siftsmall_query.fvecs %data_path%\siftsmall_groundtruth.ivecs .\bin\graph\hcnng.ivecs 1 -1
.\bin\test_guided_search %data_path%\siftsmall_base.fvecs %data_path%\siftsmall_query.fvecs %data_path%\siftsmall_groundtruth.ivecs .\bin\graph\hcnng.ivecs 1 -1
