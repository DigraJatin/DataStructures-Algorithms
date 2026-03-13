# Monotonic Stack Cheatsheet

## Comparison Operators

| Problem | L→R pop condition | R→L pop condition |
|---------|-------------------|-------------------|
| **Next Greater** (resolve) | `<` | `<=` (discard) |
| **Next Smaller** (resolve) | `>` | `>=` (discard) |
| **Prev Greater** (discard) | `<=` | `<` (resolve) |
| **Prev Smaller** (discard) | `>=` | `>` (resolve) |

- **resolve**: the popped element gets its answer assigned
- **discard**: the popped element is removed because it can't be a valid answer
- The "resolve" direction uses strict comparison; the "discard" direction uses non-strict to handle duplicates
