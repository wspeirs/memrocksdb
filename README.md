MemRocksDB
===

MemRocksDB is simply the [memcached](https://memcached.org/) API hooked to a [rocksdb](http://rocksdb.org/) backend. Any client that speaks the memcached protocol (currently text only) can be used to
interact with MemRocksDB. Unlike memcached, all values are persisted to disk via rocksdb. 
