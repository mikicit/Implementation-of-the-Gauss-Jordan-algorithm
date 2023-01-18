# Řešení soustav lineárních rovnic

## Popis

V tomto projeku byl pro řešení soustav lineárních rovnic zvolen Gauss-Jordanův eliminační algoritmus. Byly zavedeny tři režimy provozu:

1. Classic (Jednovláknové).
2. Paralelní (vícevláknové).
3. Asynchronní (vícevláknové nebo jednovláknové).

Rozšířenou matici lze zadat třemi způsoby:
1. Prostřednictvím konzoly (čtení skončí, jakmile se objeví prázdný řádek nebo EOF).
```
1 2 3
4 5 6
```
2. Čtení ze souboru.
3. Generování náhodného pro danou velikost (argument v CLI).

## CLI

Pro různé režimy provozu programu bylo zavedeno rozhraní CLI.

Při spuštění programu s argumentem --help (-h) nebo bez žádného argumentu se vypíše následující:

```
Usage: ./gauss {-h | --help |-f <file> | -c | -r <x> <y>} {-s|-a|-p} {-S|-F} 
Options:
  -h, --help Show this help message and exit
  -f <file> Read matrix from file
  -r <x> <y> Generate random matrix with size <x> <y>
  -c Enter matrx from console
  -a Use async solver
  -p Use parallel solver
  -s Use classic solver
  -S Short
  -F Full
```

## Příklady práce (argument -c)

### Soustava lineárních rovnic s 1 řešením

Vstup:
```
1 2 3
4 5 6
```
Výstup:
```
Solution:
( 3 6 )
```

### Soustava lineárních rovnic s nekonečným počtem řešení.

Vstup:
```
1 0 3
2 0 6
```
Výstup:
```
Infinite solutions: 
Particular
( 3 0 )
Span
( 0 -1 )
```

### Soustava lineárních rovnic nemá řešení.

Vstup:
```
1 2 3
0 0 6
```
Výstup:
```
No solution
```

## Srovnání výkonu v různých režimech

Pro testování výkonu byl použit operační systém Manjaro Linux se čtyřjádrovým procesorem.

```
Size 10x11                                                                                                                                                                                 
Classic
Time: 9.894e-05s
Parallel
Time: 0.0083872s
Async
Time: 0.00126633s

Size 100x101                                                                                                                                                                              
Classic
Time: 0.0276958s
Parallel
Time: 0.316384s
Async
Time: 0.0210501s

Size 500x501                                                                                                                                                                               
Classic
Time: 2.03858s
Parallel
Time: 8.41357s
Async
Time: 2.64696s

Size 1000x1001                                                                                                                                                                         
Classic
Time: 16.2057s
Parallel
Time: 34.5052s
Async
Time: 16.6399s

Size 2000x2001                                                                                                                                                                           
Classic
Time: 127.166s
Parallel
Time: 160.325s
Async
Time: 129.159s

Size 3000x3001                                                                                                                                                                    
Classic
Time: 429.501s
Parallel
Time: 506.156s
Async
Time: 433.419s
```

Je zřejmé, že při zvětšení velikosti matice bude výsledek v paralelním režimu rychlejší než výsledek v klasickém režimu.