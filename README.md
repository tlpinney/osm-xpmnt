# OSM-EXPMNTS

### Build the docker image
```
docker build -t osm-xpmnt .
```

### Download xml/bz2 openstreetmap history file 
```
curl -O https://planet.openstreetmap.org/planet/full-history/history-latest.osm.bz2
```

### Run the docker image to output tsv file 
```
touch output.tsv && docker run -v $(pwd)/history-latest.osm.bz2:/root/input.osm.bz2 -v $(pwd)/output.tsv:/root/output.tsv -i -t osm-xpmnt /root/changeset2tsv /root/input.osm.bz2 /root/output.tsv
```



### Debug the docker image
```
docker run -v $(pwd)/history-latest.osm.bz2:/root/input -v /root/output:$(pwd)/output.tsv -i -t osm-xpmnt /bin/bash
```
