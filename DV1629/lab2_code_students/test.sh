let "numPages = 1"
for noPagesMult in {1..8}
do
    let "size = 64"
    for pageSize in {1..4}
    do
        let "size = $size * 2"
        ./optimalcppv2/optimal $numPages $size mp3d.mem
    done
    let "numPages = $numPages + $numPages"
done