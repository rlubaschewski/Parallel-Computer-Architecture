# CMakeList.txt: CMake-Projekt für "PCA_04". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)
PROJECT ( Test C CXX )
# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (PCA_04 "PCA_04.cpp" "PCA_04.h")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(PCA_04 Threads::Threads)

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
