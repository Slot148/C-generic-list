# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.html).

## [1.1.0] - 2024-05-21

### Added
- `foreach` function to apply a given function to each element in the list, using an internal iterator.
- `duplicate` function to create a deep copy of a list.
- Internal `TIterator` implementation (`newIterator`, `next`, `hasNext`, `freeIterator`) to support new iteration-based features and improve extensibility.

### Fixed
- Corrected the logic in `duplicate` to properly copy values for all supported data types instead of just copying pointers.
- Ensured the `_tail` pointer is correctly updated to `NULL` when the list becomes empty after a `pop` or `delete` operation.
- Ensured the `_tail` pointer is correctly reassigned to the new last element when the old tail is removed via `delete` or `pick`.

### Changed
- Refined `destroyList` to also reset `_tail` and `_length` for a more consistent state after clearing the list.
- Improved error handling in `newIterator` to prevent creation of an iterator from a `NULL` list instance.

## [1.0.0] - 2024-05-20

### Added
- Initial release of the `Tlist` generic list library.
- Core API: `newList`, `push`, `pop`, `get`, `set`, `insert`, `delete`, `pick`, `len`, `print`, `free`.
- Support for `INT`, `FLOAT`, `DOUBLE`, `STRING`, and generic `T` pointer types with appropriate memory management.
- Object-oriented style API using function pointers.
- CMake build system and Doxygen documentation setup.