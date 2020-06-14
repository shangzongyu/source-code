#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
defmodule DictReader do
  def read_dict do
    "/usr/share/dict/words"
    |> File.read!()
    |> String.split()
    |> Enum.filter(fn word -> String.length(word) >= 3 end)
    |> Enum.reduce(%{}, &add_to_dict/2)
  end

  def signature_of(word) when is_binary(word) do
    word
    |> String.codepoints()
    |> signature_of()
  end

  def signature_of(word) when is_list(word) do
    word
    |> Enum.sort()
    |> Enum.join()
  end

  defp add_to_dict(word, result) do
    sig = signature_of(word)
    Map.update(result, sig, [ word ], &[ word | &1 ])
  end
end


defmodule Dictionary do

  @dict %{} #DictReader.read_dict

  defdelegate signature_of(word), to: DictReader

  def lookup_by_signature(sig) when is_binary(sig) do
    @dict[sig]
  end
end
