# main-ashmaize

Simple C main loop for Scavenger mine that use a ce-ashmaize fork.

This is FAST and reliable but this is NOT a complete Midnight Scavenger miner:

it's intended to be used in something else that manage the API and get the challenges.

# Get and build it

You also need my ce-ashmaize, a modified ce-ashmaize from IOHK, then you can build:

```bash
git clone https://github.com/andreabravetti/ce-ashmaize.git
cd ce-ashmaize
cargo build --release
cd ..
git clone https://github.com/andreabravetti/main-ashmaize.git
cd main-ashmaize
gcc -L../ce-ashmaize/target/release/ -o ashmaize ashmaize.c -lm -lashmaize
```

It should work on any platform supported by Rust and GCC, but I have only Linux on x86_64.

# Run a challenge

```bash
./ashmaize addr1xxxxx **D06C09 00001FFF xxx_no_pre_mine_xxx 2025-11-05T07:59:59.000Z 424085764
```

# If you like it...

If you like this software please consider sending some $ADA (and some $NIGHT?) here:

`addr1qxwlv5qskprgkawru5trypdfz3m92c3zd59tstll5zqdqhxvdnclft2ujyvn5narz4cnef2mry6msmkhnl6qdx9xm8dqatmxa3`
