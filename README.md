## Build instruction

git clone https://github.com/stefanofiorentino/s3it-tech-challenge 

cd s3it-tech-challenge 

git submodule update --init --recursive

rm -rf ./build/*

mkdir -p build && cd build

cmake ..

make 

./s3it-tech-challenge \
    --channelR=E-cadherin\(Er167Di\).tiff \
    --channelG=HistoneH3\(Yb176Di\).tiff \
    --channelB=Fibronectin\(Dy163Di\).tiff