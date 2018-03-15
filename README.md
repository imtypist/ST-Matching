# ST-Matching

ST-Matching is proposed in *Map-matching for low-sampling-rate GPS trajectories*, which is a map matching algorithm usually used for handling low sampling rate GPS trajectories. This paper is also avaliable in my repository, you can download it.

Then, I will introduce the flow of ST-Matching and how to run this program.

### Work flow of ST-Matching

In this section, I will show a flow chart of ST-Matching algorithm. **To be added...**

### What I use in this project

- PostgreSQL 10
  - NOTE : [How to operate PostgreSQL using C/C++?](https://segmentfault.com/a/1190000000628234)
  - The thing needs to know is that if you install a x64 version, you should compile the project in x64, otherwise it would be ERROR.
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

### Run it

#### Firstly, modify config.ini

You need to modify the `config.ini` in the project folder according to your database configuration, for example:

```bash
#ST-Matching配置文件,为方便处理，每一行“=”左边为配置的属性，“=”右边请空一格写入属性值，“=”左右两边请留一个空格。每行属性上一行是对其作用的解释，以“#”作为解释的开头。

#数据库名称
dbname = shanghai_osm
#数据库端口号
dbport = 5432
#数据库地址
dbaddr = 127.0.0.1
#道路表名称
roadTN = road_network
#线程数，声明使用多少线程来进行计算
threadnum = 3
#每个轨迹点最多选多少个候选点。建议为5个
K = 5
#求最优路径时选取当前值最大的top个点用作下一个点的计算
top = 3
#选取某轨迹点的候选点时，距离轨迹点的范围，单位为Km
R = 0.1
#正态分布的方差，单位为Km
sigma = 0.02
```

Usually, modifing the first four items is enough if you have no idea about the other five items.

#### Secondly, format gps data

The content of input gps file should be formatted as following, which respectively denote `id,timestamp,longitude,latitude` in order:

```bash
13301128438,2013-10-16 23:50:24,116.366653,39.938328
13301128438,2013-10-16 23:50:48,116.366623,39.937351
13301128438,2013-10-16 23:51:48,116.366722,39.933094
13301128438,2013-10-16 23:54:24,116.367302,39.921505
...
```

We should notice that the `id` segments are the same in a file, because the ST-Matching algorihm can only match one trajectory at a time.

### Acknowledgement

This project is based on the same name repository of @[AzoresCabbage](https://github.com/AzoresCabbage). I try to reconstruct the project and make it easier to use. If there is any problem, please let me know.

