# Uploading Aegis Genesis to GitHub

Recommended repository name: `aegis-genesis`

## Option A — GitHub website (easiest)

1. Sign in to GitHub at https://github.com/.
2. Click the **+** button in the upper-right corner and choose **New repository**.
3. Set **Repository name** to `aegis-genesis`.
4. Set the repository to **Public**.
5. In Description, use something like:
   `Human-governed C++17 collision-risk demonstrator presented at Robotics & AI Discovery Day 2026.`
6. Do **not** initialize the repository with a README, `.gitignore`, or license, because those are already in this package.
7. Click **Create repository**.
8. On the empty repository page, click **uploading an existing file**.
9. Open the extracted `aegis_genesis_github_ready` folder on your computer.
10. Drag **all contents inside that folder** into GitHub, preserving the `src`, `docs`, and `results` folders.
11. Use a commit message such as:
    `Publish Aegis Genesis Discovery Day 2026 poster and verified C++ source`
12. Click **Commit changes**.
13. Open the repository and confirm the README renders correctly.
14. Click the poster link in the README and confirm GitHub opens the PDF.

## Option B — Git command line

After creating an empty public repository named `aegis-genesis`:

```bash
cd path/to/aegis_genesis_github_ready
git init
git add .
git commit -m "Publish Aegis Genesis Discovery Day 2026 poster and verified C++ source"
git branch -M main
git remote add origin https://github.com/Edgar-Fu/aegis-genesis.git
git push -u origin main
```

If Git asks you to authenticate, follow GitHub's sign-in / credential prompt.

## Poster link for your resume

Once the repository is public and the default branch is `main`, the expected GitHub poster URL is:

```text
https://github.com/Edgar-Fu/aegis-genesis/blob/main/docs/Aegis_Genesis_Robotics_AI_Discovery_Day_2026_Poster.pdf
```

Open that URL in a private/incognito browser window before putting it on your resume. If it opens without requiring you to sign in, the recruiter-facing link is ready.

### Recommended resume display

Use compact linked text rather than printing the whole URL in the project title, for example:

`Aegis Genesis — Radar Collision Avoidance | Poster`

Make **Poster** the clickable link to the GitHub PDF URL above.

If you also want the code readily accessible, another good version is:

`Aegis Genesis — Radar Collision Avoidance | Poster | GitHub`

where **Poster** links directly to the PDF and **GitHub** links to:

```text
https://github.com/Edgar-Fu/aegis-genesis
```

## Final checks before adding the link to a resume

- Repository is **Public**.
- README loads normally.
- Poster opens from the README.
- `src/aegis_genesis.cpp` is visible on GitHub.
- The source SHA-256 remains:
  `ee20c87d65b9fd3915ee7ef8997c2d116078e1466746c584cc988df7511d9355`
- `results/verification_output.txt` ends with `Tests: 10/10 passed`.
- The PDF is the final version without the removed top-right event header.
