$project_root = (get-item .).parent.FullName
$build_cmd = "docker run -v ${project_root}:/src -w /src/target -u emscripten trzeci/emscripten"
$exec_cmd   = "docker run --name emrun -p 6931:6931 -v ${project_root}:/src -w /src/target -u emscripten trzeci/emscripten"

function Run {
    echo " "
    echo ==================================================
    echo "$args"
    echo --------------------
    
    Invoke-Expression "$docker_build $args"
}

mkdir ../target 2> $null 1>$null
Run $build_cmd cmake ../build
#Run $build_cmd make clean
Run $build_cmd make
copy ../src/index.html ../target/index.html

docker rm -f emrun > $null
Run $exec_cmd emrun --hostname 0.0.0.0 --no_browser index.html

pause
