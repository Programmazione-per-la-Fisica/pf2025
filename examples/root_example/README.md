# Esempio di utilizzo di ROOT e compilazione con CMake

Il codice in questa cartella ([`main.cpp`](./main.cpp)) presenta un esempio per
la generazione di un file `.gif` animato, relativo alla determinazione di
$\pi$ tramite il metodo hit-or-miss, prodotto utilizzando ROOT.

Per la compilazione abbiamo utilizzato CMake, il cui file
[`CMakeLists.txt`](./CMakeLists.txt) d'esempio è stato preparato seguendo le
istruzioni contenute in
[questa pagina](https://root.cern/manual/integrate_root_into_my_cmake_project/)
della documentazione ufficiale di ROOT.

Per compilare il codice utilizzate il comando:

```bash
cmake -S . -B build -G "Ninja Multi-Config"
```

seguito da:

```bash
cmake --build build --config Debug
```

Per eseguire il programma:

```bash
build/Debug/hit_or_miss
```

Seguono qui alcune note/consigli per l'uso di ROOT:

> [!NOTE]
> Per utilizzare le librerie provviste con ROOT è necessario utilizzare la
> versione `c++17` dello standard: `set(CMAKE_CXX_STANDARD 17)`

> [!IMPORTANT]
> Nel codice presentato non viene fatto alcun uso della gestione dinamica della
> memoria (cioè non viene fatto uso di, `new`, `delete`, puntatori o _smart
> pointer_).
>
> Per fare sì che i diversi oggetti (nell'esempio `TGraph` e `TLatex`) vengano
> disegnati correttamente, basta garantire che risultino disponibili (cioè non
> siano già stati distrutti) nel momento in cui viene invocato il metodo
> `Print()` della `canvas`.

> [!TIP]
> Al posto dell'uso diretto di valori interi, si sono utilizzati degli `enum`
> per la gestione di marker, colori, impaginazione:
>
> ```c++
> // https://root.cern.ch/doc/master/classTAttMarker.html#ATTMARKER2
> enum markers {
>   Circle = 20,
>   Cross = 47
> };
> ```
>
> al fine di rendere il codice più espressivo.
