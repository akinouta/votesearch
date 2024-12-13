@echo on

g++ -I../include/ ../src/common.cpp ../src/hcnng.cpp ../test/test_build_index.cpp -o hcnng -std=c++11 -fopenmp -O3
g++ -I../include/ ../src/common.cpp ../src/search.cpp ../test/test_search.cpp -o search -std=c++11 -fopenmp -O3
if %ERRORLEVEL% == 0 (
    echo Compilation successful.
) else (
    echo Compilation failed.
)

hcnng ../dataset/siftsmall/siftsmall/siftsmall_base.fvecs 1000 20 hcnng.ivecs
pause

search ../dataset/siftsmall/siftsmall/siftsmall_base.fvecs ../dataset/siftsmall/siftsmall/siftsmall_query.fvecs ../dataset/siftsmall/siftsmall/siftsmall_groundtruth.ivecs hcnng.ivecs 1 -1
