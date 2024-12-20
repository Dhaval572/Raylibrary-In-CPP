<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Raylib Project</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #000000;
            color: #d4d4d4;
        }

        header {
            background-color: #1e1e1e;
            color: #ffffff;
            padding: 1rem 0;
            text-align: center;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
            position: sticky;
            top: 0;
            z-index: 1000;
        }

        main {
            padding: 2rem;
            max-width: 800px;
            margin: 0 auto;
        }

        section {
            margin-bottom: 2rem;
        }

        h1, h2 {
            color: #569cd6;
        }

        ul, ol {
            margin: 0;
            padding: 0 0 0 1.5rem;
        }

        footer {
            background-color: #1e1e1e;
            color: #ffffff;
            text-align: center;
            padding: 1rem 0;
            position: fixed;
            bottom: 0;
            width: 100%;
        }

        p {
            line-height: 1.6;
        }

        pre {
            background-color: #1e1e1e;
            color: #d4d4d4;
            padding: 1rem;
            border-radius: 5px;
            overflow-x: auto;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        code {
            background-color: #1e1e1e;
            color: #d4d4d4;
            padding: 0.2rem 0.4rem;
            border-radius: 4px;
            display: block;
        }

        .code-header {
            background-color: #007acc;
            color: white;
            padding: 0.5rem;
            border-top-left-radius: 5px;
            border-top-right-radius: 5px;
            font-size: 0.9rem;
        }

        .keyword { color: #569cd6; }
        .function { color: #dcdcaa; }
        .string { color: #ce9178; }
        .comment { color: #6a9955; }

        .button {
            display: inline-block;
            padding: 0.5rem 1rem;
            margin: 0.5rem 0;
            background-color: #007acc;
            color: white;
            text-align: center;
            border-radius: 5px;
            text-decoration: none;
            transition: background-color 0.3s;
        }

        .button:hover {
            background-color: #005f99;
        }

        .card {
            background-color: #1e1e1e;
            padding: 1rem;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
            margin-bottom: 2rem;
        }

        .card h2 {
            margin-top: 0;
        }
    </style>
</head>
<body>
    <header>
        <h1>Raylib Project</h1>
    </header>
    <main>
        <section class="card">
            <h2>Introduction</h2>
            <p>Raylib is a simple and easy-to-use library to enjoy videogames programming. It is highly portable and cross-platform, making it a great choice for game development.</p>
        </section>
        <section class="card">
            <h2>Features</h2>
            <ul>
                <li>Simple and easy-to-use API</li>
                <li>Cross-platform support</li>
                <li>Extensive documentation and examples</li>
            </ul>
        </section>
        <section class="card">
            <h2>Installation</h2>
            <p>Follow these steps to install the project:</p>
            <ol>
                <li>Download the Raylib library from the official website.</li>
                <li>Extract the files to your project directory.</li>
                <li>Include the Raylib header files in your project.</li>
            </ol>
        </section>
        <section class="card">
            <h2>Usage</h2>
            <p>To use Raylib in your project, include the following code in your main file:</p>
            <div class="code-header">main.c</div>
            <pre><code><span class="keyword">#include</span> <span class="string">&quot;raylib.h&quot;</span>

<span class="keyword">int</span> <span class="function">main</span>(<span class="keyword">void</span>) {
    <span class="comment">// Initialization</span>
    <span class="function">InitWindow</span>(800, 600, <span class="string">&quot;Raylib Project&quot;</span>);
    <span class="function">SetTargetFPS</span>(60);

    <span class="comment">// Main game loop</span>
    <span class="keyword">while</span> (!<span class="function">WindowShouldClose</span>()) {
        <span class="function">BeginDrawing</span>();
        <span class="function">ClearBackground</span>(<span class="keyword">RAYWHITE</span>);
        <span class="function">DrawText</span>(<span class="string">&quot;Welcome to Raylib!&quot;</span>, 190, 200, 20, <span class="keyword">LIGHTGRAY</span>);
        <span class="function">EndDrawing</span>();
    }

    <span class="comment">// De-Initialization</span>
    <span class="function">CloseWindow</span>();

    <span class="keyword">return</span> 0;
}</code></pre>
        </section>
        <a href="https://www.raylib.com/" class="button">Learn More</a>
    </main>
    <footer>
        <p>&copy; 2024 Dhaval</p>
    </footer>
</body>
</html>
