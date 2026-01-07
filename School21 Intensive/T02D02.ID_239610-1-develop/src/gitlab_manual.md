# GitLab Quick Manual

This manual provides step-by-step instructions for common GitLab tasks, including repository setup, branching, issues, merge requests, tagging, and wiki usage.

---

## 1. Creating a Personal Repository

1. Log in to your GitLab account.
2. Click **New Project** → **Create blank project**.
3. Enter a project name.
4. Check **Initialize repository with a README**.
5. Select a `.gitignore` template suitable for your project (e.g., Python, Node, etc.).
6. Click **Create project**.

---

## 2. Creating Develop and Master Branches

1. By default, GitLab creates the `main` branch. Rename it to `master` (optional) in **Repository → Branches → Rename**.
2. Create a new branch called `develop` from `master`:
   - Go to **Repository → Branches → New branch**
   - Branch name: `develop`
   - Source: `master`
3. Click **Create branch**.

---

## 3. Setting Develop as the Default Branch

1. Go to **Settings → Repository → Default branch**.
2. Select `develop` from the dropdown.
3. Click **Save changes**.

---

## 4. Creating an Issue for the Manual

1. Navigate to **Issues → New issue**.
2. Title: `Create GitLab manual`.
3. Description: Brief explanation of the manual content.
4. Assign to yourself or the relevant team member.
5. Click **Submit issue**.

---

## 5. Creating a Branch for the Issue

1. Open the issue.
2. Click **Create merge request** → **Create a new branch**.
3. Branch name: `issue-<issue-number>` (e.g., `issue-5`).
4. Click **Create branch**.

---

## 6. Creating a Merge Request on Develop Branch

1. Go to **Merge Requests → New merge request**.
2. Source branch: `issue-<number>`.
3. Target branch: `develop`.
4. Add a title and optional description.
5. Click **Create merge request**.

---

## 7. Commenting and Accepting Merge Request

1. Open the merge request.
2. Add comments if needed.
3. Click **Merge** when ready to accept.
4. Confirm the merge.

---

## 8. Creating a Stable Version in Master with a Tag

1. Go to **Repository → Tags → New tag**.
2. Tag name: `v1.0` (or any semantic version).
3. Target branch: `master`.
4. Click **Create tag**.

---

## 9. Working with Wiki for the Project

1. Go to **Wiki → Create your first page**.
2. Add content such as guides or project documentation.
3. Click **Create page**.
4. Use the Markdown editor to format text, add links, images, and tables.

---

*End of manual.*
