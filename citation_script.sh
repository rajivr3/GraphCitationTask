export LD_LIBRARY_PATH=/software/gcc-9.2.0:/software/gcc-9.2.0/libexec:/software/gcc-9.2.0/lib:/software/gcc-9.2.0/lib64
/software/gcc-9.2.0/bin/g++ citation_mlt.cpp -o mlt --std=c++14 -pthread
./mlt "/srv/local/shared/external/dbid/exosome_dimensions_wedell_retraction-depleted_jc250-corrected.csv"
python3 stats_plotter.py
