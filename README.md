# main-ashmaize

Simple script for Scavenger mine

# Get modified ce-ashmaize

Clone `https://github.com/andreabravetti/ce-ashmaize.git` in the parent directory.

Change to ce-ashmaize and run `cargo build --release`

# Compile ashmaize

```bash
gcc -L../ce-ashmaize/target/release/ -o ashmaize ashmaize.c -lm -lashmaize
```

# Run a challenge

```bash
./ashmaize addr1xxxxx **D06C09 00001FFF xxx_no_pre_mine_xxx 2025-11-05T07:59:59.000Z 424085764
```
