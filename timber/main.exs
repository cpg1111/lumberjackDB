require Tomlex

defmodule Main do
    def init() do
        sharedConf = File.read("../config/shared.toml")
        timberConf = File.read("../config/timber.toml")
    end
end
