#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
defmodule Grep do

  def find_all(file_name, pattern) do
    File.read(file_name)
    |> find_matching_lines(pattern)
    |> truncate_lines()
  end

  # ----------

  defp find_matching_lines({:ok, content}, pattern) do
    content
    |> String.split(~r/\n/)
    |> Enum.filter(&String.match?(&1, pattern))
    |> ok_unless_empty()
  end

  defp find_matching_lines(error, _), do: error

  # ----------

  defp truncate_lines({ :ok, lines }) do
    lines
    |> Enum.map(&String.slice(&1, 0, 20))
    |> ok()
  end

  defp truncate_lines(error), do: error

  # ----------

  defp ok_unless_empty([]),     do: error("nothing found")
  defp ok_unless_empty(result), do: ok(result)

  defp ok(result),    do: { :ok,    result }
  defp error(reason), do: { :error, reason }
end
