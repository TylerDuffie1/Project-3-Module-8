#ifndef ITEMTRACKER_H
#define ITEMTRACKER_H

#include <string>
#include <map>

/**
 * @brief ItemTracker reads an input file of purchased items (one per line or space-separated)
 *        and builds frequency counts. It can also back up the counts to frequency.dat,
 *        print a report, and render a text histogram.
 *
 * Design notes:
 *  - Uses std::map<std::string,int> for deterministic ordering.
 *  - Normalizes words to lowercase and strips leading/trailing punctuation.
 *  - Public interface kept small and intention-revealing.
 */
class ItemTracker {
public:
    // Construct with path to input file (e.g., data/CS210_Project_Three_Input_File.txt)
    explicit ItemTracker(const std::string& inputPath);

    // Parse the input file and build counts. Returns true on success.
    bool Load();

    // Persist counts to "frequency.dat" in the working directory.
    // Returns true on success.
    bool WriteFrequencyBackup(const std::string& outPath = "frequency.dat") const;

    // Return frequency for a specific item (case-insensitive).
    int FrequencyOf(const std::string& rawWord) const;

    // Print "item count" lines to stdout.
    void PrintAllFrequencies() const;

    // Print "item *****" histogram lines to stdout.
    void PrintHistogram(char barChar='*') const;

private:
    std::string m_inputPath;
    std::map<std::string, int> m_counts;

    // Normalize words: lowercase, strip leading/trailing punctuation.
    static std::string Normalize(const std::string& raw);
};

#endif // ITEMTRACKER_H
