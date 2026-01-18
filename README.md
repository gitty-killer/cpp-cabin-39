# cpp-cabin-39

A small C++ tool that computes text statistics for cabin.

## Objective
- Provide quick text metrics for cabin documents.
- Report top word frequencies for fast inspection.

## Use cases
- Validate cabin drafts for repeated terms before review.
- Summarize cabin notes when preparing reports.

## Usage
c++ main.cpp -o textstats && ./textstats data/sample.txt --top 5

## Output
- lines: total line count
- words: total word count
- chars: total character count
- top words: most frequent tokens (case-insensitive)

## Testing
- run `bash scripts/verify.sh`

## Notes
- Only ASCII letters and digits are treated as word characters.
