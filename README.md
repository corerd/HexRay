# HexRay
An X-ray for your binary data.

HexRay is a lightweight binary file viewer that allows you to view the contents of
binary files in a hex format.
It provides a user-friendly interface designed to make it easier to inspect and
understand complex binary data.

## Features
- **Hex View:** Easy visualization of binary content.
- **User-Friendly Interface:** Simplified navigation through file contents.
- **Cross-Platform:** Built using the [wxWidgets](https://wxwidgets.org/) library to provide
  a consistent graphical user interface across different platforms.

## Technical Notes & Limitations

> [!NOTE]
> Currently, HexRay freezes reading files larger than 1MB.

**Why the 1MB limit?**
The application uses the `wxTextCtrl` widget to display hex data.
Because `wxTextCtrl` is not optimized for handling large volumes of text,
it attempts to calculate layout, word wrapping, and scrollbar positions for the entire content
on the main UI thread simultaneously.
This can cause the application to freeze when rendering large files.

## Advanced Implementation (Virtual View)
For handling large amounts of text more efficiently, a **Virtual View** approach is recommended.
This involves creating a custom scrollable window that only renders what is visible on the screen.

For a practical implementation of this "Virtual View" system,
please see [HexRay Mini](https://github.com/corerd/HexRayMini).
