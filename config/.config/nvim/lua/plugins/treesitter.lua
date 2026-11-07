return {
    "nvim-treesitter/nvim-treesitter",
    branch = "main",
    lazy = false,
    build = ":TSUpdate",
    config = function()
        local langs = {
            "c", "rust", "lua", "vim", "vimdoc",
            "bash", "markdown", "json", "toml",
        }

        require("nvim-treesitter").install(langs)

        vim.api.nvim_create_autocmd("FileType", {
            pattern = { "c", "rust", "lua", "vim", "help", "sh", "bash", "markdown", "json", "toml" },
            callback = function()
                vim.treesitter.start()
            end,
        })
    end,
}
