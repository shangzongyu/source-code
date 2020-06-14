#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
defmodule Anagrams do

  def anagrams_in(word) do
    word
    |> all_subsets_longer_than_three_characters()
    |> as_unique_signatures()
    |> find_in_dictionary()
    |> group_by_length()
end

  defp all_subsets_longer_than_three_characters(word) do
    word
    |> String.codepoints()
    |> Comb.subsets()
    |> Stream.filter(fn subset -> length(subset) >= 3 end)
    |> Stream.map(&List.to_string(&1))
  end

  defp as_unique_signatures(subsets) do
    subsets
    |> Stream.map(&Dictionary.signature_of/1)
  end

  defp find_in_dictionary(signatures) do
    signatures
    |> Stream.map(&Dictionary.lookup_by_signature/1)
    |> Stream.reject(&is_nil/1)
    |> Stream.concat(&(&1))
  end

  defp group_by_length(words) do
    words
    |> Enum.sort()
    |> Enum.group_by(&String.length/1)
  end

end
