# Add a module to MODULES once its RTL and testbench are written.
# CI runs `make lint test` over everything listed here.
MODULES ?= smoke

.PHONY: test lint clean $(MODULES)
test:
	@set -e; for m in $(MODULES); do echo "=== $$m ==="; $(MAKE) -s -C $$m test; done

lint:
	@set -e; for m in $(MODULES); do echo "=== lint $$m ==="; $(MAKE) -s -C $$m lint; done

clean:
	@for m in smoke sync_fifo async_fifo rr_arbiter; do $(MAKE) -s -C $$m clean; done
