# BACHELOR THESIS
## Study of the Fringe Field of Canted Cosine Theta Superconducting Magnets

During my thesis we also implemented additional functions to the C++ codebase written by my predecessors. The codebase simulates the geometry and the electromagnetic behavior of arbitrary straight or curved CCT superconducting magnets. We also utilized a third-party C++ software to calculate magnetic fields with high accuracy.

:exclamation: :exclamation: :exclamation: I'm not able to publically share the C++ codebase :exclamation: :exclamation: :exclamation:

### Abstract

Canted Cosine Theta (CCT) magnets have emerged as promising designs for compact accelerator components with high field quality. While the concept was introduced in 1969, it has recently gained increased attention from accelerator designers. The development of CCT magnets is an ongoing process, several designs have been proposed under the HITRIplus project, which aims to construct compact, reliable, and powerful synchrotrons for radiotherapy.

While the magnetic field inside CCT magnets exhibits excellent homogeneity, undesired field components arise at the magnet ends (fringe field region) due to various sources. This thesis focuses on the analysis of the fringe field in dipole CCT magnets with special emphasis on strongly curved magnets, and explores methods for the elimination of the unwanted horizontal field component (causing a vertical deflection of the beam), while ensuring optimal space utilization and efficiency.

In theory, an infinitely long straight CCT magnet consisting of two concentric coils with the same radii and opposite tilt angles produces a pure homogeneous dipole field within the aperture. However, practical considerations, such as continuous winding at different radii, introduce unwanted field components. Curved CCT magnets are better suited for larger beam deflection and introduce an additional constituent to the fringe field, which can be utilized to counteract the fringe field originating from winding progression by adjusting the handedness of the coils.

Altering the ratio of contribution from each coil to the net dipole field and the dilution of the winding geometry offer potential solutions for eliminating the net effect of unwanted field components. However, these approaches compromise the overall efficiency of the magnet. Alternatively, twisting the winding geometry has been found to be a viable and effective solution, as even a small deviation from the original winding geometry yields satisfactory results.

Finally, the magnet’s diverting ability must be set to meet the desired beam diversion angle for a given magnetic rigidity. The length of the magnet is proportional to the diversion angle, considering the bending radius and nominal dipole field strength are given. However, the dipole component of the fringe field can cause a deviation from the nominal diversion angle. We introduce a numerical method to counteracting the dipole fringe field by adjusting the length of the magnet.

