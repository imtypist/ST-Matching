# ST-Matching

ST-Matching is proposed in *Map-matching for low-sampling-rate GPS trajectories*, which is a map matching algorithm usually used for handling low sampling rate GPS trajectories. This paper is also avaliable in my repository, you can download it.

Then, I will introduce the flow of ST-Matching and how to run this program.

### Work flow of ST-Matching

In this section, I will show a flow chart of ST-Matching algorithm. **To be added...**

### What I use in this project

- PostgreSQL 10
  - NOTE : [How to operate PostgreSQL using C/C++?](https://segmentfault.com/a/1190000000628234)
- Visual Studio 2017 
  - recomended, some other IDEs are OK
- PostGIS 2.4.3
- [osm2pgsql: OpenStreetMap data to PostgreSQL converter](https://github.com/openstreetmap/osm2pgsql) 0.92.0
  - Windows users should NOTICE that, Cross-compilation problems with osm2pgsql are documented on github. Whilst these problems are being worked on, an alternative compilation path for windows users targeting **Cygwin** has been used. [Installation for Windows is here](https://wiki.openstreetmap.org/wiki/Osm2pgsql#Windows)

### Preprocess of OSM

Before running the program, we should import map file `*.osm` into database. So we can utilize osm2pgsql to do this. Before running osm2pgsql, you first **MUST** create your postgresql database and **enable postgis** on it. Then, you can import through command as following:

```bash
osm2pgsql -s -U postgres -d nameofdatabase /file/path/toosm/fileorpbf/name.osm -W
```

which `U` denotes your username, `d` denotes database name, or you can get more details through `osm2pgsql -help`. Then, enter your database's password, there will be some screen outputs like this:

```bash
Using XML parser.
Processing: Node(899k 179.9k/s) Way(124k 62.48k/s) Relation(1560 1560.00/s)  parse time: 8s
Node stats: total(899390), max(5463903487) in 5s
Way stats: total(124957), max(567723766) in 2s
Relation stats: total(1569), max(8055906) in 1s
...
...
node cache: stored: 899390(100.00%), storage efficiency: 50.00% (dense blocks: 0, sparse nodes: 899390), hit rate: 100.01%

Osm2pgsql took 20s overall
```

It's done.

### Acknowledgement

This project is based on the same name repository of @[AzoresCabbage](https://github.com/AzoresCabbage). I try to reconstruct the project and make it easier to use. If there is any problem, please let me know.

