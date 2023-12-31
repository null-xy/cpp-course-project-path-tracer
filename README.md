# Tracey - The Next Generation Path Tracer

The project aims to produce software that renders a three-dimensional image that
simulates real-world illumination.

## Group

- Jukka Aho
- Aleksi Kääriäinen
- Yuting Xie

## Build instructions

The project uses CMake, thus the standard way of building project is as follows:

```bash
cmake -S . -B build
cmake --build build
```

Building documentation needs Doxygen to be installed. Building documentation:

```bash
cmake --build build --target doc
```

The documentation will be built to `build/doc/html`. Also, more or less
up-to-day documentation is found from <https://tracey-docs.netlify.app/>.
Deployment to Netlify can be done with a command:

```bash
netlify deploy --prod -d build/doc/html
```

Building tests with target `tests`:

```bash
cmake --build build --target tests
cd build
ctest
```

## Repository organization

Your project implementation should follow the skelaton organization in this
repository. See readme.md files in each folder.

## Project Implementation

You must use git repository for the work on the project, making frequent enough
commits so that the project group (and course staff) can follow the progress.

The completed project work will be demonstrated to the group's advisor at a demo
session. The final demonstrations are arranged on week 50. After the final
demonstrations project group evaluates another project, and self-evaluates own
project. In addition, project members will give a confidential individual
assessment of each group member.

The course staff should be able to easily compile the project work using
makefile and related instructions provided in the git repository. The final
output should be in the **master branch** of the git repository.

## Working practices

Each project group is assigned an advisor from the project teaching personnel.
There will be a dedicated Teams channel for each project topic to facilitate
discussion between the groups in the same topic and the advisor.

**The group should meet weekly.** The weekly meeting does not need to be long if
there are no special issues to discuss, and can be taken remotely as voice/video
chat on the group Teams channel (or Zoom or other similar tool), preferably at a
regular weekly time. In the meeting the group updates:

- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After the meetings, the meeting notes will be committed to the project
  repository in the `Meeting-notes.md` file.
    * The commits within the week should have some commit messages referring to
      the meeting notes so that the project advisor can follow the progress.
    * **The meeting notes should be in English.**

> Everyone may not be able to participate to all meetings, but at least a couple
> of members should be present in each meeting. Regular absence from meetings
> will affect in individual evaluation.

## Source code documentation

It is strongly recommended to use Doxygen to document your source code. Please
go over the *Project Guidelines* for details.

## TODOs (Date)

You can create a list of TODOs in this file. The recommended format is:

- Complete class implementation **foo**. Assigned to \<Member 1\>
- Test ...
