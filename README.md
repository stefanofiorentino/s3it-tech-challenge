## Build instruction

git clone https://github.com/stefanofiorentino/s3it-tech-challenge 

cd s3it-tech-challenge 

git submodule update --init --recursive

rm -rf ./build/*

mkdir -p build && cd build

cmake ..

make s3it-tech-challenge

cd ..

./build/s3it-tech-challenge \
    --rChannel ./data/images/E-cadherin\(Er167Di\).tiff \
    --bChannel ./data/images/Fibronectin\(Dy163Di\).tiff \
    --gChannel ./data/images/HistoneH3\(Yb176Di\).tiff \
    --single_cell_mask ./data/single-cell-mask/single_cell_mask.tiff
